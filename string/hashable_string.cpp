#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <memory>

#define HASHABLE_STRING_SEGMENT_TREE
#ifdef HASHABLE_STRING_SEGMENT_TREE
#include <atcoder/segtree>
#include <atcoder/lazysegtree>
#endif // HASHABLE_STRING_SEGMENT_TREE

namespace hashable_string {

using namespace std;
using ull = uint64_t;

const ull suggest_mods_cnt = 5;
const ull sh_base = 26; // only works in [A, Z] for now
const ull sh_mods[6] = {
    static_cast<ull>(1e9 + 7),
    static_cast<ull>(1e9 + 9),
    static_cast<ull>(1e9 + 13),
    static_cast<ull>(1e9 + 17),
    static_cast<ull>(1e9 + 21),
    212370440130137957ULL // 不建议用这么大的模数 可能会爆ull
};

ull qpow(ull base, ull times, ull mod = UINT64_MAX)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    ull ans = qpow(base, times >> 1, mod) % mod;
    ans = ans * ans % mod;
    if(times & 1) ans = ans * base % mod;

    return ans;
}

// uses 2 mods
class hashable_string {
    string s;
    ull hash0, hash1;
    vector<ull> prefix0, prefix1;

    inline ull convert_char(char c) const { // [0, 26) or [0, sh_base)
        return static_cast<ull>(c - 'A');
    }

    inline void hash_str(const string &s, ull mod, ull &res, vector<ull> &prefix) const {
        int len = s.size();
        prefix.resize(len + 1);
        prefix[0] = 0;

        res = 0;
        for (int i = 1; i <= len; i++) {
            res = (res * sh_base + convert_char(s[i - 1])) % mod;
            prefix[i] = res;
        }
    }

    // sub string: [l, r]
    inline ull hash_substr(int l, int r, ull mod, const vector<ull> &prefix) const {
        ull res = prefix[r];
        ull sub = qpow(sh_base, r - l + 1, mod) * prefix[l - 1] % mod;
        return (res + mod - sub) % mod;
    }

public:
    inline void set(const string &v) {
        s = v;
        hash_str(s, sh_mods[0], hash0, prefix0);
        hash_str(s, sh_mods[1], hash1, prefix1);
    }

    inline int length() const {
        return s.length();
    }

    // O(1)
    inline pair<ull, ull> hash_str() const {
        return make_pair(hash0, hash1);
    }

    // O(log{r-l}) 主要计算量在于pow的计算 可以通过预计算降低到O(1)
    inline pair<ull, ull> hash_substr(int l, int r) const { // 1 <= l <= r <= len
        return make_pair<ull, ull>(
            hash_substr(l, r, sh_mods[0], prefix0),
            hash_substr(l, r, sh_mods[1], prefix1)
        );
    }

    // remember to compare length
    bool operator==(const hashable_string &other) const {
        return length() == other.length() && hash_str() == other.hash_str();
    }

    hashable_string() {
        set("");
    }
};

#ifdef HASHABLE_STRING_SEGMENT_TREE
// uses n mods
class hashable_string_segment_tree {
protected:
    string s;

    static ull char_to_num(char c) {
        return c - 'A';
    }

protected:
    struct S {
        ull h[suggest_mods_cnt], pw[suggest_mods_cnt];

        static S default_value(char c) {
            S res;
            for(ull i = 0; i < suggest_mods_cnt; i++) {
                res.h[i] = char_to_num(c);
                res.pw[i] = sh_base;
            }
            return res;
        }

        static S empty_value() {
            S res;
            for(ull i = 0; i < suggest_mods_cnt; i++) {
                res.h[i] = 0;
                res.pw[i] = 1;
            }
            return res;
        }
    };

    static S op(S l, S r) {
        S res;
        for(ull i = 0; i < suggest_mods_cnt; i++) {
            res.h[i] = (l.h[i] * r.pw[i] % sh_mods[i] + r.h[i]) % sh_mods[i];
            res.pw[i] = l.pw[i] * r.pw[i] % sh_mods[i];
        }
        return res;
    }

    static S e() {
        return S::empty_value();
    }

    std::unique_ptr<atcoder::segtree<S, op, e>> seg;

public:
    void set(const string &s) {
        this->s = s;

        // build segment tree
        vector<S> v(s.length());
        for(ull i = 0; i < s.length(); i++) {
            v[i] = S::default_value(s[i]);
        }
        seg = std::make_unique<atcoder::segtree<S, op, e>>(v);
    }

    // pos: [1, length]
    void modify(ull pos, char c) {
        seg->set(pos - 1, S::default_value(c));
    }

    // l, r: [1, length] -> str[l, r]
    vector<ull> hash(ull l, ull r) {
        vector<ull> res(suggest_mods_cnt);
        auto prod = seg->prod(l - 1, r);
        for(ull i = 0; i < suggest_mods_cnt; i++) {
            res[i] = prod.h[i];
        }
        return res;
    }
};
#endif // HASHABLE_STRING_SEGMENT_TREE

int hashable_string_toolkit() {
    hashable_string a, b;
    a.set("ABCDABC");
    b.set("AB");

    for(int i = b.length(); i <= a.length(); i++) {
        if(b.hash_str() == a.hash_substr(i - b.length() + 1, i)) {
            cout << i << " ";
        }
    }
    cout << endl;

#ifdef HASHABLE_STRING_SEGMENT_TREE
    hashable_string_segment_tree seg1, seg2;
    seg1.set("ABCABCABCABCABCABCABCABCABCABC");
    seg2.set("ACCABCABCABCABCABCABCABCABCABB");
    seg2.modify(2, 'B');
    auto ha = seg1.hash(1, 30), hb = seg2.hash(1, 30);
    for(ull i = 0; i < suggest_mods_cnt; i++) {
        cout << ha[i] << " ";
    }
    cout << endl;
    for(ull i = 0; i < suggest_mods_cnt; i++) {
        cout << hb[i] << " ";
    }
    cout << endl;
#endif // HASHABLE_STRING_SEGMENT_TREE

    return 0;
}

} // namespace hashable_string
