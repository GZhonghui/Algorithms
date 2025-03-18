/*

Tarjan
Tarjan's strongly connected components algorithm  
强连通分量

【Wikipedia】在有向图的数学理论中，如果一个图的每一个顶点都可从该图其他任意一点到达，则称该**图是强连通**的。
在任意有向图中**能够实现强连通的部分**我们称其为强连通分量。判断一个图是否为强连通以及找到一个图强连通分量只需要线性时间（Θ(V + E)）
【什么是强连通，强连通是定义在点对之间的】在本身可能**不是强连通的有向图**G中，如果一对顶点u和v之间在每个方向上都有一条路径，则称它们是强连通的。
强连通的二元关系是一个**等价关系**，其**等价类**的导出子图称为**强连通分量**。
如果将每个强连通分量收缩为单个顶点，则得到的图是一个**有向无环图**。

本算法在做什么？
输入一个有向图，计算其强连通分量（像是在说废话）

https://atcoder.jp/contests/typical90/tasks/typical90_u
http://poj.org/problem?id=2186 Popular Cows

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#include <unordered_map>
#include <cstdint>
using namespace std;
const int maxn=100000 + 1;
int N,M,Index,Low[maxn],Dfn[maxn],Size[maxn];
int Num,Belong[maxn],in[maxn],out[maxn]; // Belong: final answer
bool inStack[maxn];
stack<int> Stack;
vector<int> G[maxn];
void Tarjan(int x)
{
    Dfn[x]=Low[x]=++Index;
    inStack[x]=true;
    Stack.push(x);
    for(int i=0;i<G[x].size();i++)
    {
        int to=G[x][i];
        if(!Dfn[to])
        {
            Tarjan(to);
            if(Low[to]<Low[x])
                Low[x]=Low[to];
        }
        else if(inStack[to]&&Dfn[to]<Low[x])
        {
            Low[x]=Dfn[to];
        }
    }
    if(Dfn[x]==Low[x])
    {
        int to;
        Num++;
        do
        {
            to=Stack.top();
            Stack.pop();
            inStack[to]=false;
            Belong[to]=Num;
            Size[Num]++;
        }while(to!=x);
    }
}
void init()
{
    memset(Belong,0,sizeof(Belong));
    memset(inStack,0,sizeof(inStack));
    memset(Size,0,sizeof(Size));
    memset(Low,0,sizeof(Low));
    memset(Dfn,0,sizeof(Dfn));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    for(int i=1;i<=N;i++) G[i].clear();
    Index=Num=0;
}

int main()
{
    int n,m,x,y;
    scanf("%d %d",&n,&m);

    N = n;
    init();

    for(int i=0;i<m;i+=1)
    {
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
    }

    for(int i=1;i<=N;i+=1)
    {
        if(!Dfn[i]) Tarjan(i);
    }

    std::unordered_map<int,int> counter;
    for(int i=1;i<=N;i+=1)
    {
        int _belong = Belong[i];
        if(!counter.count(_belong))
        {
            counter[_belong] = 0;
        }
        counter[_belong] += 1;
    }

    int64_t ans = 0;
    for(auto i = counter.begin(); i != counter.end(); i++)
    {
        int64_t _size = i->second;
        int64_t local = (_size * (_size - 1)) >> 1;
        ans += local;
    }
    printf("%lld",ans);

    return 0;
}
