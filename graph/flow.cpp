/*

网络流

max_flow_dinic
max flow 最大流算法
最大流的Dinic算法，实现简单但是时间复杂度不是最优秀的

min_cost_max_flow_dinic
min cost max flow 最小费用最大网络流
基于Dinic的最小费用流算法，每条边除了容量以外还有单独的费用，算法目标是找到总花费最小的最大流方案  
最终的方案，首先是保证最大流，其实才是保证最小费用  
每条边的费用，是单位费用，有x的流量，就有kx的费用

*/

#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>

namespace max_flow_dinic {
using namespace std;

const int maxn=1024; // 节点数
const int inf=0xffffff;

struct Edge
{
    int from,to,cap,flow;
    Edge(int from,int to,int cap,int flow):
        from(from),to(to),cap(cap),flow(flow){}
};

class Dinic
{
protected:
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
public:
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
int dinic_example()
{
    Dinic *solver=new Dinic;

    // init
    // add_edge
    // calc_max_flow

    delete solver;

    return 0;
}

} // namespace max_flow_dinic

namespace min_cost_max_flow_dinic {
using namespace std;

const int maxn=256; // 节点数
const int inf=0xffffff;

struct Edge
{
    int from,to,cap,flow,cost;
    Edge(int fr,int to,int ca,int fl,int co)
    {
        this->from=fr,this->to=to,this->cap=ca,this->flow=fl,this->cost=co;
    }
};

class Dinic
{
protected:
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn],inq[maxn];
    int s,t,dis[maxn],a[maxn],p[maxn];
public:
    // 节点范围：[1,n]
    void init(int s,int t,int n)
    {
        this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    // Cost是流量的单位花费，每条边是不同的
    void AddEdge(int Start,int End,int Cap,int Cost)
    {
        edges.push_back(Edge(Start,End,Cap,0,Cost));
        edges.push_back(Edge(End,Start,0,0,-Cost));

        G[Start].push_back(edges.size()-2);
        G[End].push_back(edges.size()-1);
    }
protected:
    bool BellmanFord(int &flow,int &cost)
    {
        for(int i=1;i<=t;i++) dis[i]=inf;
        memset(inq,0,sizeof(inq));

        dis[s]=0,inq[s]=true;a[s]=inf;p[s]=0;
        queue<int> Q;Q.push(s);

        while(!Q.empty())
        {
            int now=Q.front();Q.pop();
            inq[now]=false;

            for(int i=0,_size=G[now].size();i<_size;i++)
            {
                Edge &e=edges[G[now][i]];
                if(e.cap>e.flow&&dis[e.to]>dis[now]+e.cost)
                {
                    p[e.to]=G[now][i];
                    dis[e.to]=dis[now]+e.cost;
                    a[e.to]=min(a[now],e.cap-e.flow);

                    if(!inq[e.to])
                    {
                        Q.push(e.to);
                        inq[e.to]=true;
                    }
                }
            }
        }

        if(dis[t]==inf) return false;

        flow+=a[t];
        cost+=dis[t]*a[t];

        int now=t;
        while(now!=s)
        {
            edges[p[now]].flow+=a[t];
            edges[p[now]^1].flow-=a[t];
            now=edges[p[now]].from;
        }
        return true;
    }
public:
    int MinCost()
    {
        int flow=0,cost=0;

        while(BellmanFord(flow,cost));

        return cost;
    }
};
int min_cost_max_flow_example()
{
    Dinic *solver=new Dinic;

    // init
    // add_edge
    // calc_min_cost

    delete solver;

    return 0;
}

} // namespace min_cost_max_flow_dinic
