/*

生成树相关算法 Spanning tree

minimum_spanning_tree
最小生成树 Minimum Spanning Tree
- Kruskal's algorithm
- Prim's algorithm

spanning_tree_counting
生成树计数相关

*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

// 最小生成树
namespace minimum_spanning_tree {

class MinimumSpanningTree {
public:
    virtual void solve() = 0;
};

// TODO
class Kruskal : public MinimumSpanningTree {
public:
    void solve() override;
};

// TODO
class Prim : public MinimumSpanningTree {
public:
    void solve() override;
};

} // namespace minimum_spanning_tree

// 生成树计数
// 代码年久失修
namespace spanning_tree_counting {
using namespace std;
typedef long long ll;
const int maxn = 25;
ll a[maxn][maxn],d[maxn][maxn],g[maxn][maxn];
int t,n,m;
ll solve(ll G[][maxn],int N)
{
    ll res = 1;
    for(int i = 1;i <= N;i++)
    {
        for(int j = i + 1;j <= N;j++)
        {
            while(G[j][i])
            {
                ll o = G[i][i] / G[j][i];
                for(int k = 1;k <= N;k++)
                {
                    G[i][k] = G[i][k] - G[j][k] * o;
                    swap(G[i][k],G[j][k]);
                }
            }
            res *= -1;
        }
        res *= G[i][i];
    }
    return res;
}
int toolkit()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        memset(g,0,sizeof(g));
        int u,v;
        scanf("%d%d",&n,&m);
        while(m--)
        {
            scanf("%d%d",&u,&v);
            d[u][u]++,d[v][v]++;
            a[u][v] = a[v][u] = 1;
        }
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                g[i][j] = d[i][j] - a[i][j];
            }
        }
        ll ans = solve(g,n - 1);
        printf("%lld\n",abs(ans));
    }
    return 0;
}

} // namespace spanning_tree_counting