/*

最近公共祖先 Lowest Common Ancestor

*/

#include <cstring>
#include <iostream>
#include <vector>

// copied from: https://oi-wiki.org/graph/lca/
namespace lca {

constexpr int MXN = 2e5 + 8;
using namespace std;
vector<int> v[MXN];
vector<int> w[MXN];

int fa[MXN][31], cost[MXN][31], dep[MXN];
int n, m;
int a, b, c;

// dfs，用来为 lca 算法做准备。接受两个参数：dfs 起始节点和它的父亲节点。
void dfs(int root, int fno) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    fa[root][0] = fno;
    dep[root] = dep[fa[root][0]] + 1;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
    // 2^(i-1) 的祖先节点。
    for (int i = 1; i < 31; ++i) {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
        cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
    }
    // 遍历子节点来进行 dfs。
    int sz = v[root].size();
    for (int i = 0; i < sz; ++i) {
        if (v[root][i] == fno) continue;
        cost[v[root][i]][0] = w[root][i];
        dfs(v[root][i], root);
    }
}

// lca。用倍增算法算取 x 和 y 的 lca 节点。
pair<int, int> lca(int x, int y) {
    // 令 y 比 x 深。
    if (dep[x] > dep[y]) swap(x, y);
    // 令 y 和 x 在一个深度。
    int tmp = dep[y] - dep[x], ans = 0;
    for (int j = 0; tmp; ++j, tmp >>= 1)
        if (tmp & 1) ans += cost[y][j], y = fa[y][j];
    // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先。
    if (y == x) return {x, ans};
    // 不然的话，找到第一个不是它们祖先的两个点。
    for (int j = 30; j >= 0 && y != x; --j) {
        if (fa[x][j] != fa[y][j]) {
            ans += cost[x][j] + cost[y][j];
            x = fa[x][j];
            y = fa[y][j];
        }
    }
    // 返回结果。
    ans += cost[x][0] + cost[y][0];
    return {x, ans};
}

// [1, n]
void init(int _n) {
    // 初始化表示祖先的数组 fa，代价 cost 和深度 dep。
    memset(fa, 0, sizeof(fa));
    memset(cost, 0, sizeof(cost));
    memset(dep, 0, sizeof(dep));

    n = _n;

    // 初始化树边和边权
    for (int i = 1; i <= n; ++i) {
        v[i].clear();
        w[i].clear();
    }
}

// edges count: n - 1
void add_edge(int a, int b, int distance) {
    v[a].push_back(b);
    v[b].push_back(a);
    w[a].push_back(distance);
    w[b].push_back(distance);
}

void lca_toolkit() {
    init(3);
    add_edge(1, 2, 2);
    add_edge(2, 3, 3);
    dfs(2, 0); // select 2 as root

    auto res = lca(1, 3);
    cout << "lca = " << res.first << ", distance = " << res.second << endl;
}

} // namespace lca