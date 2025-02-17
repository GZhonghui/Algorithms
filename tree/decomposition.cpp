/*

树链剖分 heavy_light_decomposition
主要思路是：将树形结构拆分成路径 使用管理区间的数据结构 管理树上路径
需要用到线段树（其他的管理区间数据结构也可以）

heavy_light_decomposition_edge
按边剖分

heavy_light_decomposition_vertex
按点剖分

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

// 按边剖分
namespace heavy_light_decomposition_edge {
using namespace std;
const int maxn=1e5+10;
bool lazy[maxn<<2];
int from[maxn],to[maxn],dis[maxn];
int N,_time,_left,_right,_pos,new_value;
vector<int> G[maxn];
int tr_max[maxn<<2],tr_min[maxn<<2];
int flat[maxn],restore[maxn];
int fa[maxn],son[maxn],sum[maxn];
int dep[maxn],top[maxn];
void reverse(int node)
{
    int max_value=tr_max[node];
    int min_value=tr_min[node];
    tr_max[node]=-min_value;
    tr_min[node]=-max_value;
}
void pushdown(int node)
{
    lazy[node]=false;
    lazy[node<<1]=!lazy[node<<1];
    lazy[node<<1|1]=!lazy[node<<1|1];
    reverse(node<<1);
    reverse(node<<1|1);
}
void pushup(int node)
{
    tr_max[node]=max(tr_max[node<<1],tr_max[node<<1|1]);
    tr_min[node]=min(tr_min[node<<1],tr_min[node<<1|1]);
}
void bulid(int node,int l,int r)
{
    lazy[node]=false;
    if(l==r)
    {
        tr_max[node]=tr_min[node]=0;
        return;
    }
    int mid=(l+r)>>1;
    bulid(node<<1,l,mid);
    bulid(node<<1|1,mid+1,r);
    pushup(node);
}
int pre_dfs(int now,int father,int depth)
{
    int max_nodes=0;
    fa[now]=father;
    dep[now]=depth;
    son[now]=-1,sum[now]=1;
    for(int i=0,_size=G[now].size();i<_size;i++)
    {
        int to=G[now][i];
        if(to==father) continue;
        int nodes=pre_dfs(to,now,depth+1);
        if(nodes>max_nodes)
        {
            max_nodes=nodes;
            son[now]=to;
        }
        sum[now]+=nodes;
    }
    return sum[now];
}
void dfs(int now,int top_node)
{
    if(fa[now]!=-1)
    {
        _time++;
        flat[now]=_time;
        restore[_time]=now;
    }
    top[now]=top_node;
    if(son[now]==-1) return;
    dfs(son[now],top_node);
    for(int i=0,_size=G[now].size();i<_size;i++)
    {
        int to=G[now][i];
        if(to==son[now]||to==fa[now]) continue;
        dfs(to,to);
    }
}
void change(int node,int l,int r)
{
    if(l==r)
    {
        tr_max[node]=tr_min[node]=new_value;
        return;
    }
    if(lazy[node]) pushdown(node);
    int mid=(l+r)>>1;
    if(_pos<=mid) change(node<<1,l,mid);
    else change(node<<1|1,mid+1,r);
    pushup(node);
}
void update(int node,int l,int r)
{
    if(_left<=l&&r<=_right)
    {
        lazy[node]=!lazy[node];
        reverse(node);
        return;
    }
    if(lazy[node]) pushdown(node);
    int mid=(l+r)>>1;
    if(_left<=mid) update(node<<1,l,mid);
    if(_right>mid) update(node<<1|1,mid+1,r);
    pushup(node);
}
int ask(int node,int l,int r)
{
    if(_left<=l&&r<=_right) return tr_max[node];
    if(lazy[node]) pushdown(node);
    int mid=(l+r)>>1;
    bool exist_left=(_left<=mid);
    bool exist_right=(_right>mid);
    if(exist_left&&exist_right)
        return max(ask(node<<1,l,mid),ask(node<<1|1,mid+1,r));
    if(exist_left) return ask(node<<1,l,mid);
    return ask(node<<1|1,mid+1,r);
}
void init()
{
    for(int i=1;i<=N;i++) G[i].clear();
    _time=0;
}
void Demo()
{
    int T;scanf("%d",&T);
    char oper[16];int x,y;
    while(T--)
    {
        scanf("%d",&N);init();
        for(int i=1;i<N;i++)
        {
            scanf("%d %d %d",&from[i],&to[i],&dis[i]);
            G[from[i]].push_back(to[i]);
            G[to[i]].push_back(from[i]);
        }
        pre_dfs(1,-1,1);dfs(1,1);bulid(1,1,N-1);
        for(int i=1;i<N;i++)
        {
            int target=dep[from[i]]>dep[to[i]]?from[i]:to[i];
            _pos=flat[target];
            new_value=dis[i];
            change(1,1,N-1);
        }
        int ans,target;
        bool found;
        while(true)
        {
            scanf("%s",oper);
            if(oper[0]=='D') break;
            scanf("%d %d",&x,&y);
            switch(oper[0])
            {
                case 'C':
                    new_value=y;
                    target=dep[from[x]]>dep[to[x]]?from[x]:to[x];
                    _pos=flat[target];
                    change(1,1,N-1);
                break;
                case 'Q':
                    found=false;
                    while(top[x]!=top[y])
                    {
                        if(dep[top[x]]>dep[top[y]])
                        {
                            _left=flat[top[x]],_right=flat[x];
                            if(!found) ans=ask(1,1,N-1),found=true;
                            else ans=max(ans,ask(1,1,N-1));
                            x=fa[top[x]];
                        }else
                        {
                            _left=flat[top[y]],_right=flat[y];
                            if(!found) ans=ask(1,1,N-1),found=true;
                            else ans=max(ans,ask(1,1,N-1));
                            y=fa[top[y]];
                        }
                    }
                    if(x!=y)
                    {
                        if(dep[x]<dep[y])
                            _left=flat[son[x]],_right=flat[y];
                        else
                            _left=flat[son[y]],_right=flat[x];
                        if(!found) ans=ask(1,1,N-1),found=true;
                        else ans=max(ans,ask(1,1,N-1));
                    }
                    printf("%d\n",ans);
                break;
                case 'N':
                    while(top[x]!=top[y])
                    {
                        if(dep[top[x]]>dep[top[y]])
                        {
                            _left=flat[top[x]],_right=flat[x];
                            update(1,1,N-1);
                            x=fa[top[x]];
                        }else
                        {
                            _left=flat[top[y]],_right=flat[y];
                            update(1,1,N-1);
                            y=fa[top[y]];
                        }
                    }
                    if(x!=y)
                    {
                        if(dep[x]<dep[y])
                            _left=flat[son[x]],_right=flat[y];
                        else
                            _left=flat[son[y]],_right=flat[x];
                        update(1,1,N-1);
                    }
                break;
            }
        }
    }
}

} // namespace heavy_light_decomposition_edge

// 按点剖分
namespace heavy_light_decomposition_vertex {
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

} // namespace heavy_light_decomposition_vertex