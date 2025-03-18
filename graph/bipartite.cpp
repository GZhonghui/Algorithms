/*

bipartite graph 二分图相关

bipartite_graph_matching
二分图匹配

hungarian_algorithm
匈牙利算法
TODO: 二分图匹配的问题描述
匈牙利算法通过**增广路**的方式，求二分图的**最大匹配**
DFS实现
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

namespace bipartite_graph_matching {
    // 匈牙利算法
    // DFS实现
    namespace hungarian_algorithm {
        using namespace std;
        const int maxn=305;
        int p,ll[maxn],lr[maxn];
        bool vis[maxn];
        vector<int> G[maxn];
        bool find(int x)
        {
            for(int i=0;i<G[x].size();i++)
            {
                int to=G[x][i];
                if(!vis[to])
                {
                    vis[to]=true;
                    if(!lr[to]||find(lr[to]))
                    {
                        ll[x]=to;
                        lr[to]=x;
                        return true;
                    }
                }
            }
            return false;
        }
        void init()
        {
            for(int i=1;i<=p;i++) G[i].clear();
        }
        void Demo()
        {
            init();
            int ans=0;
            memset(ll,0,sizeof(ll));
            memset(lr,0,sizeof(lr));
            for(int i=1;i<=p;i++)
            {
                if(!ll[i])
                {
                    memset(vis,0,sizeof(vis));
                    if(find(i)) ans++;
                }
            }
        }
    }
    
    // 带花树
    namespace blossom_tree {
        // TODO
    }
}