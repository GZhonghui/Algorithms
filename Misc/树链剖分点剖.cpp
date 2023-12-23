#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=5e4+10;
int fa[maxn],son[maxn],sum[maxn];
int top[maxn],dep[maxn];
int restore[maxn],flat[maxn];
int N,M,P,Value[maxn],p;
int _time,_left,_right,_pos;
long long lazy[maxn*4],Data[maxn*4];
vector<int> G[maxn];
int pre_dfs(int now,int father,int depth)
{
    int max_node=0;
    fa[now]=father;
    dep[now]=depth;
    sum[now]=1;
    son[now]=-1;
    for(int i=0,_size=G[now].size();i<_size;i++)
    {
        int to=G[now][i];
        if(to==father)  continue;
        int nodes=pre_dfs(to,now,depth+1);
        if(nodes>max_node)
        {
            max_node=nodes;
            son[now]=to;
        }
        sum[now]+=nodes;
    }
    return sum[now];
}
void dfs(int now,int top_node)
{
    _time++;
    flat[now]=_time;
    restore[_time]=now;
    top[now]=top_node;
    if(son[now]==-1) return;
    dfs(son[now],top_node);
    for(int i=0,_size=G[now].size();i<_size;i++)
    {
        int to=G[now][i];
        if(to==fa[now]||to==son[now]) continue;
        dfs(to,to);
    }
}
void bulid(int node,int l,int r)
{
    lazy[node]=0;
    if(l==r)
    {
        Data[node]=Value[restore[l]];
        return;
    }
    int mid=(l+r)>>1;
    bulid(node<<1,l,mid);
    bulid((node<<1)+1,mid+1,r);
    Data[node]=Data[node<<1]+Data[(node<<1)+1];
}
void pushdown(int node,int l,int r)
{
    int mid=(l+r)>>1;
    lazy[node<<1]+=lazy[node];
    lazy[(node<<1)+1]+=lazy[node];
    Data[node<<1]+=(mid-l+1)*lazy[node];
    Data[(node<<1)+1]+=(r-mid)*lazy[node];
    lazy[node]=0;
}
void update(int node,int l,int r)
{
    if(_left<=l&&r<=_right)
    {
        Data[node]+=(r-l+1)*p;
        lazy[node]+=p;
        return;
    }
    if(lazy[node]) pushdown(node,l,r);
    int mid=(l+r)>>1;
    if(_left<=mid) update(node<<1,l,mid);
    if(_right>mid) update((node<<1)+1,mid+1,r);
    Data[node]=Data[node<<1]+Data[(node<<1)+1];
}
int ask(int node,int l,int r)
{
    if(l==r) return Data[node];
    if(lazy[node]) pushdown(node,l,r);
    int mid=(l+r)>>1;
    if(_pos<=mid) return ask(node<<1,l,mid);
    else return ask((node<<1)+1,mid+1,r);
}
void init()
{
    for(int i=1;i<=N;i++) G[i].clear();
    _time=0;
}
void DemoUpdate(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>=dep[top[y]])
        {
            _left=flat[top[x]],_right=flat[x];
            update(1,1,N);
            x=fa[top[x]];
        }else
        {
            _left=flat[top[y]],_right=flat[y];
            update(1,1,N);
            y=fa[top[y]];
        }
    }
    _left=min(flat[x],flat[y]),_right=max(flat[x],flat[y]);
    update(1,1,N);
}
int main()
{
    return 0;
}