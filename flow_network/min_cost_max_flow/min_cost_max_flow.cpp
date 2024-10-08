#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;

const int maxn=256;
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
public:
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
    int MinCost()
    {
        int flow=0,cost=0;

        while(BellmanFord(flow,cost));

        return cost;
    }
};
int main()
{
    // init
    // add_edge
    // calc_min_cost
    return 0;
}
