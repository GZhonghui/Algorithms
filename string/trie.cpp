/*

trie 字典树

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>

namespace trie {
    using namespace std;
    typedef int64_t ll;

    const ll maxlen = 5e5 + 8;

    class trie {
        vector<vector<ll>> next;
        ll fa[maxlen], cnt;
        bool exist[maxlen];

        inline uint8_t ci(char c) {
            return c - 'a';
        }

    public:
        trie() : next(maxlen, vector<ll>(26, -1)) {
            memset(exist, false, sizeof(exist));
            memset(fa, -1, sizeof(fa));
            cnt = 0;
        }

        void insert(
            const string &s,
            void (*fun)(ll id) = nullptr,
            void (*end)(ll id) = nullptr,
            void (*rev)(ll id) = nullptr
        ) {
            ll now = 0;
            for(char c : s) {
                if(next[now][ci(c)] == -1) {
                    next[now][ci(c)] = ++cnt;
                    fa[cnt] = now;
                }
                now = next[now][ci(c)];
                if(fun) {
                    fun(now);
                }
            }
            exist[now] = true;

            if(end) end(now);

            if(rev) {
                while(now) {
                    rev(now);
                    now = fa[now];
                }
            }
        }

        bool find(const string &s) {
            ll now = 0;
            for(char c : s) {
                ll to = next[now][ci(c)];
                if(to == -1) {
                    return false;
                }
                now = to;
            }
            return exist[now];
        }

        inline ll f(ll id) { return fa[id]; }
        inline void s(ll id, void (*f)(ll id)) {
            for(uint8_t i = 0; i < 26; i++) {
                if(next[id][i] != -1) f(next[id][i]);
            }
        }
    };

    inline void toolkit() {
        trie t;

        t.insert("hello", [](ll id) {
            cout << id << ", ";
        });
        cout << (t.find("hell") ? "Y" : "N") << endl;
    }
} // namespace trie