#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1024;
const int inf=0xffffff;
struct Edge
{
    int from,to,cap,flow;
};
struct Dinic
{
    vector<int> G[maxn];
    vector<Edge> edges;
    bool vis[maxn];
    int s,t,d[maxn],cur[maxn];
    void init(int s,int t,int n)
    {
        this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        G[from].push_back(edges.size()-2);
        G[to].push_back(edges.size()-1);
    }
    bool bfs()
    {
        memset(vis,0,sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s]=0;
        vis[s]=true;
        while(!Q.empty())
        {
            int now=Q.front();Q.pop();
            for(int i=0;i<G[now].size();i++)
            {
                Edge& e=edges[G[now][i]];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to]=d[now]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x,int a)
    {
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int& i=cur[x];i<G[x].size();i++)
        {
            Edge& e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0)
            {
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(!a) break;
            }
        }
        return flow;
    }
    int maxFlow()
    {
        int ans=0;
        while(bfs())
        {
            memset(cur,0,sizeof(cur));
            ans+=dfs(s,inf);
        }
        return ans;
    }
};
int main()
{
    return 0;
}
