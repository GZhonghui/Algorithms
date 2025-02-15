/*

splay 是一种平衡二叉树
同时 splay 也可以用于处理区间操作

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>

// TODO: 应该自己实现一份基于 node 和指针的版本
namespace splay {

} // namespace splay

// 作为平衡树使用的 Splay 树
// copied from: https://oi-wiki.org/ds/splay/
namespace splay_oiwiki {

constexpr int N = 100005; // 最大节点数

struct Splay {
protected:
    int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];

    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }

    bool get(int x) { return x == ch[fa[x]][1]; } // 获取 x 和其父节点的关系

    void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z) ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }

    // Splay 操作规定：每访问一个节点 x 后都要强制将其旋转到根节点
    void splay(int x) {
        for (int f = fa[x]; f = fa[x], f; rotate(x))
            if (fa[f]) rotate(get(x) == get(f) ? f : x);
        rt = x;
    }

public:
    void ins(int k) {
        if (!rt) {
            val[++tot] = k;
            cnt[tot]++;
            rt = tot;
            maintain(rt);
            return;
        }
        int cur = rt, f = 0;
        while (1) {
            if (val[cur] == k) {
                cnt[cur]++;
                maintain(cur);
                maintain(f);
                splay(cur);
                break;
            }
            f = cur;
            cur = ch[cur][val[cur] < k];
            if (!cur) {
                val[++tot] = k;
                cnt[tot]++;
                fa[tot] = f;
                ch[f][val[f] < k] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                break;
            }
        }
    }

    int rk(int k) {
        int res = 0, cur = rt;
        while (1) {
            if (k < val[cur]) {
                cur = ch[cur][0];
            } else {
                res += sz[ch[cur][0]];
                if (!cur) return res + 1;
                if (k == val[cur]) {
                    splay(cur);
                    return res + 1;
                }
                res += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }

    int kth(int k) {
        int cur = rt;
        while (1) {
            if (ch[cur][0] && k <= sz[ch[cur][0]]) {
                cur = ch[cur][0];
            } else {
                k -= cnt[cur] + sz[ch[cur][0]];
                if (k <= 0) {
                    splay(cur);
                    return val[cur];
                }
                cur = ch[cur][1];
            }
        }
    }

    int pre() { // 前驱
        int cur = ch[rt][0];
        if (!cur) return cur;
        while (ch[cur][1]) cur = ch[cur][1];
        splay(cur);
        return cur;
    }

    int nxt() { // 后继
        int cur = ch[rt][1];
        if (!cur) return cur;
        while (ch[cur][0]) cur = ch[cur][0];
        splay(cur);
        return cur;
    }

    void del(int k) {
        rk(k);
        if (cnt[rt] > 1) {
            cnt[rt]--;
            maintain(rt);
            return;
        }
        if (!ch[rt][0] && !ch[rt][1]) {
            clear(rt);
            rt = 0;
            return;
        }
        if (!ch[rt][0]) {
            int cur = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        if (!ch[rt][1]) {
            int cur = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        int cur = rt;
        int x = pre();
        fa[ch[cur][1]] = x;
        ch[x][1] = ch[cur][1];
        clear(cur);
        maintain(rt);
    }

    // 获取节点 id 的值
    int value(int id) {
        return val[id];
    }

    // 获取树的大小
    int size() {
        return sz[rt];
    }

    // 获取树的根节点
    int root() {
        return rt;
    }
};

void toolkit() {
    Splay tree;

    for(int i = 5; i >= 1; i--) {
        tree.ins(i);
        assert(tree.rk(i) == 1); // 1-indexed
    }
    assert(tree.size() == 5);

    tree.del(3);
    assert(tree.rk(4) == 3);
    assert(tree.kth(3) == 4);

    int _size = tree.size();
    for(int i = 1; i <= _size; i++) {
        assert(tree.rk(tree.kth(i)) == i);
    }

    // 获取前缀
    tree.ins(3); // 确保 3 存在 并且将 3 旋转到根节点
    assert(tree.value(tree.pre()) == 2); // 前缀的值是 2
    tree.del(3);

    // 后继同理
}

} // namespace splay_oiwiki

// 使用 splay 维护区间
// splay 常数比线段树大 但是可以支持更复杂的操作 比如区间翻转
// copied from: https://oi-wiki.org/ds/splay/
namespace splay_oiwiki_range {
using namespace std;

constexpr int N = 100005; // 最大节点数

struct Splay {
protected:
    int n, rt, tot, fa[N], ch[N][2], val[N], sz[N], lazy[N];

    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1; }

    bool get(int x) { return x == ch[fa[x]][1]; }

    void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = lazy[x] = 0;
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z) ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }

    void splay(int x, int goal = 0) {
        if (goal == 0) rt = x;
        while (fa[x] != goal) {
            int f = fa[x], g = fa[fa[x]];
            if (g != goal) {
                if (get(f) == get(x))
                    rotate(f);
                else
                    rotate(x);
            }
            rotate(x);
        }
    }

    void tagrev(int x) {
        std::swap(ch[x][0], ch[x][1]);
        lazy[x] ^= 1;
    }

    void pushdown(int x) {
        if (lazy[x]) {
            tagrev(ch[x][0]);
            tagrev(ch[x][1]);
            lazy[x] = 0;
        }
    }

    int build(int l, int r, int f, int *a) {
        if (l > r) return 0;
        int mid = (l + r) / 2, cur = ++tot;
        val[cur] = a[mid], fa[cur] = f;
        ch[cur][0] = build(l, mid - 1, cur, a);
        ch[cur][1] = build(mid + 1, r, cur, a);
        maintain(cur);
        return cur;
    }

    void print(int x, vector<int> &ans) {
        pushdown(x);
        if (ch[x][0]) print(ch[x][0], ans);
        if (val[x] && val[x] != INT32_MAX) ans.push_back(val[x]); // 哨兵节点不加入答案
        if (ch[x][1]) print(ch[x][1], ans);
    }

    int kth(int k) {
        int cur = rt;
        while (1) {
            pushdown(cur);
            if (ch[cur][0] && k <= sz[ch[cur][0]]) {
                cur = ch[cur][0];
            } else {
                k -= 1 + sz[ch[cur][0]];
                if (k <= 0) {
                    splay(cur);
                    return cur;
                }
                cur = ch[cur][1];
            }
        }
    }

public:
    void build(int n, int *a) {
        a[0] = 0, a[n + 1] = INT32_MAX; // 哨兵
        this-> n = n;
        rt = build(0, n + 1, 0, a);
    }

    void reverse(int l, int r) {
        int L = kth(l), R = kth(r + 2);
        splay(L), splay(R, L);
        int tmp = ch[ch[L][1]][0];
        tagrev(tmp);
    }

    // 打印整棵树
    void print(vector<int> &ans) {
        print(rt, ans);
    }
};

void toolkit() {
    int n = 5, a[N];
    for (int i = 1; i <= n; i++) a[i] = i * i; // 初始化数组 需要是有序的

    Splay tree;
    
    auto p = [&]() {
        vector<int> ans;
        tree.print(ans);
        for(int i : ans) cout << i << " "; cout << endl;
    };

    tree.build(n, a); // a must be 1-indexed
    p();

    tree.reverse(1, 3); // 翻转区间 [1, 3]
    p();

    tree.reverse(2, 4);
    p();
}

} // namespace splay_oiwiki_range