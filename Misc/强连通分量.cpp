#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<vector>
using namespace std;
const int maxn=10010;
int N,M,Index,Low[maxn],Dfn[maxn],size[maxn];
int Num,Belong[maxn],in[maxn],out[maxn];
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
            size[Num]++;
        }while(to!=x);
    }
}
void init()
{
    memset(Belong,0,sizeof(Belong));
    memset(inStack,0,sizeof(inStack));
    memset(size,0,sizeof(size));
    memset(Low,0,sizeof(Low));
    memset(Dfn,0,sizeof(Dfn));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    for(int i=1;i<=N;i++) G[i].clear();
    Index=Num=0;
}
void Demo()
{
    for(int i=1;i<=N;i++)
    {
        if(!Dfn[i]) Tarjan(i);
    }
}
int main()
{
    return 0;
}
