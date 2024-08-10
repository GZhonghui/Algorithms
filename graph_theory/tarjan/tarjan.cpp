// https://atcoder.jp/contests/typical90/tasks/typical90_u

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<vector>
#include<unordered_map>
#include<cstdint>
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
