// https://atcoder.jp/contests/typical90/tasks/typical90_m 单源最短路径模板题

#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

#include<cstdint>
#include<cstring>

typedef int64_t ll;

using namespace std;

const ll maxn = 100000 + 1;
const ll inf = 1e18;

struct Edge{
    ll to,dis;
};

struct Node{
    ll id,dis;
    bool operator< (const Node& r) const{
        return dis>r.dis;
    }
};

struct Dijkstra
{
public:
    // rebuild graph
    void init(ll n) // nodes range: [1,n]
    {
        this->n = n;
        edges.clear();
        for(ll i=1;i<=n;i++) G[i].clear();
    }

    void add_edge(ll start, ll end, ll distance)
    {
        Edge e={end,distance};
        edges.push_back(e);
        G[start].push_back(edges.size()-1);
    }

    void calc(ll start_id)
    {
        init();

        d[start_id]=0;
        Node start={start_id,0};
        priority_queue<Node> Q;
        Q.push(start);
        while(!Q.empty())
        {
            Node now=Q.top();Q.pop();
            ll x=now.id;
            if(done[x]) continue;
            done[x]=true;
            for(int i=0;i<G[x].size();i++)
            {
                Edge& e=edges[G[x][i]];
                if(d[e.to]>now.dis+e.dis)
                {
                    d[e.to]=now.dis+e.dis;
                    Node Ins={e.to,d[e.to]};
                    Q.push(Ins);
                }
            }
        }
    }

    ll query(int target)
    {
        return d[target];
    }

    void copy_result(ll* buffer)
    {
        memcpy(buffer,d,sizeof(ll)*(n+1));
    }

protected:
    // recalc distance
    void init()
    {
        for(int i=1;i<=n;i++) done[i]=false,d[i]=inf;
    }

protected:
    vector<Edge> edges;
    vector<int> G[maxn];
    ll n,m,d[maxn];
    bool done[maxn];
}solver;

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    solver.init((ll)n);
    for(int i=0;i<m;i+=1)
    {
        int x,y,d;
        scanf("%d %d %d",&x,&y,&d);
        solver.add_edge((ll)x,(ll)y,(ll)d);
        solver.add_edge((ll)y,(ll)x,(ll)d);
    }

    ll from_1[maxn],from_n[maxn];
    solver.calc(1);
    solver.copy_result(from_1);
    solver.calc(n);
    solver.copy_result(from_n);

    return 0;
}