// https://acm.hdu.edu.cn/showproblem.php?pid=2544 最短路

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn=105;
const int inf=0xffffff;
struct Edge{
    int to,dis;
};
struct Node{
    int id,dis;
    bool operator< (const Node& r) const{
        return dis>r.dis;
    }
};
vector<Edge> edges;
vector<int> G[maxn];
int n,m,d[maxn];
bool done[maxn];
void init()
{
    for(int i=1;i<=n;i++) G[i].clear(),done[i]=false,d[i]=inf;
}
int main()
{
    int x,y,z;
    //freopen("in.txt","r",stdin);
    while(true)
    {
        scanf("%d %d",&n,&m);
        if(!n&&!m) break;
        init();
        while(m--)
        {   
            scanf("%d %d %d",&x,&y,&z);
            Edge e={y,z};
            edges.push_back(e);
            G[x].push_back(edges.size()-1);
            e.to=x;
            edges.push_back(e);
            G[y].push_back(edges.size()-1);
        }
        d[1]=0;
        Node start={1,0};
        priority_queue<Node> Q;
        Q.push(start);
        while(!Q.empty())
        {
            Node now=Q.top();Q.pop();
            int x=now.id;
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
        printf("%d\n",d[n]);
    }
    return 0;
}