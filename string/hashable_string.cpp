#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

namespace hashable_string {

using namespace std;
using ull = uint64_t;

const ull sh_base = 26; // only works in [A, Z] for now
const ull sh_mods[2] = {212370440130137957ULL, static_cast<ull>(1e9 + 7)};

ull qpow(ull base, ull times, ull mod = UINT64_MAX)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    ull ans = qpow(base, times >> 1, mod) % mod;
    ans = ans * ans % mod;
    if(times & 1) ans = ans * base % mod;

    return ans;
}

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

} // namespace hashable_string

int hashable_string_toolkit() {
    hashable_string::hashable_string a, b;
    a.set("ABCDABC");
    b.set("AB");

    for(int i = b.length(); i <= a.length(); i++) {
        if(b.hash_str() == a.hash_substr(i - b.length() + 1, i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}