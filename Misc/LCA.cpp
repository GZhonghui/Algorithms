#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=10010;
struct Edge
{
    int to,distance;
};
struct LCA
{
    int dp[2*maxn][64],dis[maxn];
    int depth[2*maxn],dfs_order[2*maxn];
    int n,in[maxn],_time;
    vector<int> G[maxn];
    vector<Edge> edges;
    void pre_dfs(int now,int fa,int dep,int distance)
    {
        dfs_order[++_time]=now;
        depth[_time]=dep;
        in[now]=_time;
        dis[now]=distance;
        for(int i=0,_size=G[now].size();i<_size;i++)
        {
            int to=edges[G[now][i]].to;
            if(to==fa) continue;
            pre_dfs(to,now,dep+1,distance+edges[G[now][i]].distance);
            dfs_order[++_time]=now;
            depth[_time]=dep;
        }
    }
    void pre_cal()
    {
        int a,b;
        for(int i=1;i<=n*2-1;i++) dp[i][0]=i;
        for(int j=1;(1<<j)<=n*2-1;j++)
        {
            for(int i=1;i+(1<<j)-1<=n*2-1;i++)
            {
                a=dp[i][j-1],b=dp[i+(1<<(j-1))][j-1];
                dp[i][j]=depth[a]<depth[b]?a:b;
            }
        }
    }
    int rmq(int x,int y)
    {
        int k=0,a,b;
        while((1<<(k+1))<=y-x+1) k++;
        a=dp[x][k],b=dp[y-(1<<k)+1][k];
        return depth[a]<depth[b]?a:b;
    }
    int lca(int x,int y)
    {
        int left=min(in[x],in[y]),right=max(in[x],in[y]);
        return dfs_order[rmq(left,right)];
    }
    void init()
    {
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();_time=0;
    }
};
int main()
{
    return 0;
}