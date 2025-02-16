/*

partial_sum 前缀和

一维的前缀和 我们都很熟悉了

partial_sum_2d
## 2维前缀和（いもす法）
From AtCoder Twitter:
![2d_partial_sum (From AtCoder Twitter)](./2d_partial_sum_01.jpg)
这种方法适用于**范围加减**，一个矩形范围内所有的格子都+k
可以范围查询（一个矩形范围内的和），当然也可以单点查询

## 普通2维前缀和
基础的实现，范围查询可以，但是不能范围加减

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

namespace partial_sum {
using namespace std;
using ll = int64_t;

// TODO
class partial_sum {

};

class partial_sum_2d { // all api 1-indexed!
protected:
    ll n, m;
    vector< vector<ll> > data, sum;
    vector< vector<bool> > vis;

    ll dfs(ll x, ll y) {
        if(vis[x][y]) return sum[x][y];

        vis[x][y] = true;
        ll &res = sum[x][y];

        res = 0;
        if(!x && !y) {
            res = data[0][0];
        } else if(!x) {
            res = data[x][y] + dfs(x, y - 1);
        } else if(!y) {
            res = data[x][y] + dfs(x - 1, y);
        } else {
            res = data[x][y] + dfs(x - 1, y) + dfs(x, y - 1) - dfs(x - 1, y - 1);
        }

        return res;
    }

public:
    void init(ll n, ll m) {
        this->n = n, this->m = m;
        data = vector< vector<ll> >(n + 2, vector<ll>(m + 2, 0));
    }

    // 1-indexed
    // [x1, x2] -> [1, n] [y1, y2] -> [1, m]
    void range_add(pair<ll, ll> x, pair<ll, ll> y, ll value) {
        data[x.second + 1][y.second + 1] += value;
        data[x.first][y.second + 1] -= value;
        data[x.second + 1][y.first] -= value;
        data[x.first][y.first] += value;
    }

    void build() {
        sum = vector< vector<ll> >(n + 2, vector<ll>(m + 2, 0));
        vis = vector< vector< bool> >(n + 2, vector<bool>(m + 2, false));
        dfs(n, m);

        data = sum;
        vis = vector< vector< bool> >(n + 2, vector<bool>(m + 2, false));
        dfs(n, m);
    }

    // 1-indexed
    ll range_sum(pair<ll, ll> x, pair<ll, ll> y) {
        return (
            sum[x.second][y.second]
            - sum[x.first - 1][y.second]
            - sum[x.second][y.first - 1]
            + sum[x.first - 1][y.first - 1]
        );
    }
};

// https://atcoder.jp/contests/typical90/tasks/typical90_cc
// 基础二维前缀和
void toolkit1() {
    const ll maxl = 5000;
    partial_sum_2d solver;
    solver.init(maxl, maxl);

    ll n, k, a, b;
    cin >> n >> k;
    for(ll i = 0; i < n; i++) {
        cin >> a >> b;
        solver.range_add({a, a}, {b, b}, 1);
    }
    solver.build();

    k = k + 1;
    ll res = 0;
    for(ll x = k; x <= maxl; x++) for(ll y = k; y <= maxl; y++) {
        res = max(res, solver.range_sum({x - k + 1, x}, {y - k + 1, y}));
    }
    cout << res << endl;
}

// https://atcoder.jp/contests/typical90/tasks/typical90_ab
// 2维前缀和
// 二次元いもす法
// https://x.com/e869120/status/1388262816101007363/photo/1
// 这题挺经典的
// 或许2维线段树也可以
// （之前）卡了挺久的，为什么我的写法不可以？数据范围搞错了
// 下面的代码是可以AC的
void toolkit2() {
    const ll maxl = 1000;
    partial_sum_2d solver;
    solver.init(maxl, maxl);

    ll n, lx, ly, rx, ry;
    cin >> n;
    for(ll i = 0; i < n; i++) {
        cin >> lx >> ly >> rx >> ry;
        solver.range_add({lx + 1, rx}, {ly + 1, ry}, 1);
    }
    solver.build();

    vector<ll> ans(n + 1, 0);
    for(ll i = 1; i <= maxl; i++) for(ll j = 1; j <= maxl; j++) {
        ll area = solver.range_sum({i, i}, {j, j});
        ans[area] += 1;
    }
    for(ll i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}

} // namespace partial_sum