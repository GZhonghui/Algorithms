/*

SPFA 单点最短路算法
支持负边权
代码年久失修

*/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1024;
const int inf=0xffffff;
int N,M;
struct Edge
{
    int to,dis;
    Edge(int to,int dis)
    {
        this->to=to,this->dis=dis;
    }
};
struct SPFA
{
    vector<int> G[maxn];
    vector<Edge> edges;
    int s,n,d[maxn],cnt[maxn];
    bool inq[maxn];
    void init(int s,int n)
    {
        this->s=s,this->n=n;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int dis)
    {
        edges.push_back(Edge(to,dis));
        G[from].push_back(edges.size()-1);
    }
    bool Bellman()
    {
        queue<int> Q;Q.push(s);
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) d[i]=(i==s)?0:inf;
        inq[s]=true;
        while(!Q.empty())
        {
            int now=Q.front();Q.pop();
            inq[now]=false;
            for(int i=0,_size=G[now].size();i<_size;i++)
            {
                Edge &e=edges[G[now][i]];
                if(d[e.to]>d[now]+e.dis)
                {
                    d[e.to]=d[now]+e.dis;
                    if(!inq[e.to])
                    {
                        Q.push(e.to);
                        inq[e.to]=true;
                        if(++cnt[e.to]>n) return false;
                    }
                }
            }
        }
        return true;
    }
    bool NegativeCycle()
    {
        queue<int> Q;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) d[i]=0,inq[i]=true,Q.push(i);
        while(!Q.empty())
        {
            int now=Q.front();Q.pop();
            inq[now]=false;
            for(int i=0,_size=G[now].size();i<_size;i++)
            {
                Edge &e=edges[G[now][i]];
                if(d[e.to]>d[now]+e.dis)
                {
                    d[e.to]=d[now]+e.dis;
                    if(!inq[e.to])
                    {
                        Q.push(e.to);
                        inq[e.to]=true;
                        if(++cnt[e.to]>n+1) return true;
                    }
                }
            }
        }
        return false;
    }
};
