/*

树的直径
暂时还没有测试

*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdint>
#include <vector>

namespace tree_diameter {
using namespace std;
typedef int64_t ll;
const ll maxn = 2e5 + 8;

struct Edge {
    ll to, weight;
};

class Tree {
protected:
    ll n;
    vector<Edge> edges;
    vector<ll> G[maxn];

public:
    // [1, n]
    void init(ll n) {
        this->n = n;
        edges.clear();
        for (ll i = 1; i <= n; i++) {
            G[i].clear();
        }
    }

    void add_edge(ll u, ll v, ll w) {
        edges.push_back({v, w});
        G[u].push_back(edges.size() - 1);
        edges.push_back({u, w});
        G[v].push_back(edges.size() - 1);
    }
protected:
    void dfs(ll x, ll fa, ll dist, ll &max_dist, ll &v) {
        if(dist > max_dist) {
            max_dist = dist;
            v = x;
        }
        for(ll i = 0; i < G[x].size(); i++) {
            const Edge &e = edges[G[x][i]];
            if(e.to == fa) continue;
            dfs(e.to, x, dist + e.weight, max_dist, v);
        }
    }

    void dfs_dist(ll x, ll fa, ll dist, ll *dists) {
        dists[x] = max(dists[x], dist);
        for(ll i = 0; i < G[x].size(); i++) {
            const Edge &e = edges[G[x][i]];
            if(e.to == fa) continue;
            dfs_dist(e.to, x, dist + e.weight, dists);
        }
    }

public:
    pair<ll, ll> diameter(ll *dists = nullptr) { // sizeof(dists) >= n + 1
        ll l = 0, r = 0, max_dist = 0;
        dfs(1, 0, 0, max_dist = 0, l);
        dfs(l, 0, 0, max_dist = 0, r);

        if(dists) {
            memset(dists, 0, sizeof(ll) * (n + 1));
            dfs_dist(l, 0, 0, dists);
            dfs_dist(r, 0, 0, dists);
        }

        return make_pair(l, r);
    }
};

inline void toolkit() {
    ll n = 5;
    Tree tree;
    tree.init(n);
    tree.add_edge(1, 2, 1);
    tree.add_edge(1, 3, 2);
    tree.add_edge(2, 4, 3);
    tree.add_edge(2, 5, 4);
    auto [l, r] = tree.diameter();
    cout << l << " " << r << endl;
}

} // namespace tree_diameter