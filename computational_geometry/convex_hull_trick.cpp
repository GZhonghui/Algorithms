/*

Convex Hull Trick（简称 CHT）

我们需要支持两种操作
添加直线：将新的线性函数加入到集合中
查询最值：给定一个 x，找到集合中使得 ax+b 取得最小（或最大）值的那条直线

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <cmath>
#include <set>

// copied from: https://codeforces.com/blog/entry/51275?#comment-351410
namespace convex_hull_trick_binary_search {

using namespace std;

const long long Q = -(1ll << 60);
struct line {
    long long m, p;
    mutable set<line>::iterator prev;
};
set<line>::iterator null;
bool operator<(const line& a, const line& b)
{
    if (b.p != Q && a.p != Q) {
        return a.m < b.m;
    }
    if (b.p == Q) {
        if (a.prev == null)
            return true;
        bool ok = true;
        if ((a.prev->m - a.m) < 0)
            ok = !ok;
        if (ok) {
            return (a.p - a.prev->p) < (a.prev->m - a.m) * b.m;
        }
        else {
            return (a.p - a.prev->p) > (a.prev->m - a.m) * b.m;
        }
    }
    else {
        if (b.prev == null)
            return false;
        bool ok = true;
        if ((b.prev->m - b.m) < 0)
            ok = !ok;
        if (ok) {
            return !((b.p - b.prev->p) < a.m * (b.prev->m - b.m));
        }
        else {
            return !((b.p - b.prev->p) > a.m * (b.prev->m - b.m));
        }
    }
}
class convex_hull {
public:
    set<line> convex;
    set<line>::iterator next(set<line>::iterator ii)
    {
        set<line>::iterator gg = ii;
        gg++;
        return gg;
    }
    set<line>::iterator prev(set<line>::iterator ii)
    {
        set<line>::iterator gg = ii;
        gg--;
        return gg;
    }
    bool bad(set<line>::iterator jj)
    {
        set<line>::iterator ii, kk;
        if (jj == convex.begin())
            return false;
        kk = next(jj);
        if (kk == convex.end())
            return false;
        ii = prev(jj);
        line a = *ii, c = *kk, b = *jj;
        bool ok = true;
        if ((b.m - a.m) < 0)
            ok = !ok;
        if ((b.m - c.m) < 0)
            ok = !ok;
        if (ok) {
            return (c.p - b.p) * (b.m - a.m) <= (a.p - b.p) * (b.m - c.m);
        }
        else {
            return (c.p - b.p) * (b.m - a.m) >= (a.p - b.p) * (b.m - c.m);
        }
    }
    void del(set<line>::iterator ii)
    {
        set<line>::iterator jj = next(ii);
        if (jj != convex.end()) {
            jj->prev = ii->prev;
        }
        convex.erase(ii);
    }
    void add(long long m, long long p)
    {
        null = convex.end();
        line g;
        g.m = m;
        g.p = p;
        set<line>::iterator ii = convex.find(g);
        if (ii != convex.end()) {
            if (ii->p >= p)
                return;
            del(ii);
        }
        convex.insert(g);
        ii = convex.find(g);
        set<line>::iterator jj = next(ii);
        if (jj != convex.end())
            jj->prev = ii;
        if (ii != convex.begin()) {
            ii->prev = prev(ii);
        }
        else {
            ii->prev = convex.end();
        }
        if (bad(ii)) {
            del(ii);
            return;
        }
        jj = next(ii);
        while (jj != convex.end() && bad(jj)) {
            del(jj);
            jj = next(ii);
        }
        if (ii != convex.begin()) {
            jj = prev(ii);
            while (ii != convex.begin() && bad(jj)) {
                del(jj);
                jj = prev(ii);
            }
        }
    }
    long long query(long long x)
    {
        null = convex.end();
        line y;
        y.m = x;
        y.p = Q;
        set<line>::iterator ii = convex.lower_bound(y);
        ii--;
        return ii->m * x + ii->p;
    }
};

inline void convex_hull_trick_binary_search_toolkit() {
    convex_hull ch;
    ch.add(2,0);
    ch.add(3,0);
    cout<<ch.query(4)<<endl;
    cout<<ch.query(-4)<<endl;
}

} // namespace convex_hull_trick_binary_search

// copied from: https://kazuma8128.hatenablog.com/entry/2018/02/28/102130
namespace li_chao_segment_tree {

using namespace std;
using ll = int64_t;

const ll ll_inf = 1e18;

template <typename T, const T id> // id is the minimum value of T
class convex_hull_trick {
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
        ~node() {
            if (lch) delete lch;
            if (rch) delete rch;
        }
    };

private:
    const int n;
    const vector<T> pos;
    node *root;

public:
    // pos_ is the set of possible queries' x values
    // it should be processed by sort() and unique()
    convex_hull_trick(const vector<T>& pos_) : n(pos_.size()), pos(pos_), root(nullptr) {}
    ~convex_hull_trick() {
        if (root) delete root;
    }
    void insert(T a, T b) {
        line l(a, b);
        root = modify(root, 0, n - 1, l);
    }
    T get(T x) const {
        int t = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
        assert(t < n && pos[t] == x);
        return sub(root, 0, n - 1, t);
    }

private:
    node* modify(node *p, int lb, int ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(pos[lb]) >= l.get(pos[lb]) && p->l.get(pos[ub]) >= l.get(pos[ub])) return p;
        if (p->l.get(pos[lb]) <= l.get(pos[lb]) && p->l.get(pos[ub]) <= l.get(pos[ub])) {
            p->l = l;
            return p;
        }
        int c = (lb + ub) / 2;
        if (p->l.get(pos[c]) < l.get(pos[c])) swap(p->l, l);
        if (p->l.get(pos[lb]) <= l.get(pos[lb]))
            p->lch = modify(p->lch, lb, c, l);
        else
            p->rch = modify(p->rch, c + 1, ub, l);
        return p;
    }
    T sub(node *p, int lb, int ub, int t) const {
        if (!p) return id;
        if (ub - lb == 0) return p->l.get(pos[t]);
        int c = (lb + ub) / 2;
        if (t <= c) return max(p->l.get(pos[t]), sub(p->lch, lb, c, t));
        return max(p->l.get(pos[t]), sub(p->rch, c + 1, ub, t));
    }
};

inline void li_chao_segment_tree_toolkit() {
    convex_hull_trick<ll, -ll_inf> ch(vector<ll>{1, 2, 3, 4, 5});
    ch.insert(1, 1);
    ch.insert(2, 2);
    ch.insert(3, 3);
    cout << ch.get(3) << endl; // query max value at x = 3
    // use minus to query min value
}

} // namespace li_chao_segment_tree