#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
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
struct Dinic
{
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn],inq[maxn];
    int s,t,dis[maxn],a[maxn],p[maxn];
    void init(int s,int t,int n)
    {
        this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int Start,int End,int Cap,int Cost)
    {
        edges.push_back(Edge(Start,End,Cap,0,Cost));
        edges.push_back(Edge(End,Start,0,0,-Cost));
        G[Start].push_back(edges.size()-2);
        G[End].push_back(edges.size()-1);
    }
    bool BellmanFord(int &flow,int &cost)
    {
        for(int i=1;i<=t;i++) dis[i]=inf;
        memset(inq,0,sizeof(inq));
        queue<int> Q;
        dis[s]=0,inq[s]=true;a[s]=inf;
        Q.push(s);p[s]=0;
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
}ac;
int main()
{
	return 0;
}
