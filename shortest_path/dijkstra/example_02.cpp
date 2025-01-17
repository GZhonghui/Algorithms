// https://atcoder.jp/contests/typical90/tasks/typical90_m 单源最短路径模板题

#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

#include<cstdint>
#include<cstring>

using namespace std;
typedef int64_t ll;

namespace Dijkstra {

using namespace std;
typedef int64_t ll;

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
            for(ll i=0;i<G[x].size();i++)
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

    ll query(ll target)
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
        for(ll i=1;i<=n;i++) done[i]=false,d[i]=inf;
    }

protected:
    vector<Edge> edges;
    vector<ll> G[maxn];
    ll n,m,d[maxn];
    bool done[maxn];
}solver;

} // namespace Dijkstra

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    Dijkstra::solver.init((ll)n);
    for(int i=0;i<m;i+=1)
    {
        int x,y,d;
        scanf("%d %d %d",&x,&y,&d);
        Dijkstra::solver.add_edge((ll)x,(ll)y,(ll)d);
        Dijkstra::solver.add_edge((ll)y,(ll)x,(ll)d);
    }

    ll from_1[Dijkstra::maxn],from_n[Dijkstra::maxn];
    Dijkstra::solver.calc(1);
    Dijkstra::solver.copy_result(from_1);
    Dijkstra::solver.calc(n);
    Dijkstra::solver.copy_result(from_n);

    for(int i=1;i<=n;i+=1)
    {
        cout << from_1[i]+from_n[i] << endl; // printf("%d\n",from_1[i]+from_n[i]);
    }

    return 0;
}