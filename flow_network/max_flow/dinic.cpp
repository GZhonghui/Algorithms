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
    Edge(int from,int to,int cap,int flow):
        from(from),to(to),cap(cap),flow(flow){}
};

class Dinic
{
public:
    vector<Edge> edges;
    vector<int> G[maxn];
    int s,t,d[maxn],cur[maxn];
    bool vis[maxn];
public:
    //起点、终点和节点数目
    // 节点ID：[1,n]
    void init(int s,int t,int n)
    {
        this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    // 每条边都有容量
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));

        G[from].push_back(edges.size()-2);
        G[to].push_back(edges.size()-1);
    }
protected:
    bool bfs()
    {
        memset(vis,0,sizeof(vis));

        queue<int> Q;
        vis[s]=true;
        Q.push(s);
        d[s]=0;

        while(!Q.empty())
        {
            int now=Q.front();
            Q.pop();

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
                a-=f;
                flow+=f;
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;

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
    Dinic *solver=new Dinic;

    // init
    // add_edge
    // calc_max_flow

    delete solver;

    return 0;
}
