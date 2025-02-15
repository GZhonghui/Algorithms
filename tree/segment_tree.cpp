/*

segment_tree
线段树 自己实现的版本 有 lazy 标记
修改支持：修改为定值；查询支持：Min、Max、Sum

例题推荐：
https://vjudge.net/problem/HDU-1698
https://vjudge.net/problem/POJ-3237#google_vignette
https://acm.hdu.edu.cn/showproblem.php?pid=1698 Just a Hook
https://atcoder.jp/contests/typical90/tasks/typical90_ac
https://codeforces.com/gym/102566/problem/F Magic Wand
http://poj.org/problem?id=3237 Tree

segment_tree_2d
二维线段树，支持区间修改，区间查询
可以支持的修改：加减，修改为目标值（等）
可以支持的查询：最大值，最小值，和（等）
Lazy标记

*/

#include <iostream>
#include <cstdio>
#include <algorithm>

namespace segment_tree {

using namespace std;
const int maxn=100010;

// 线段树模板
struct SGTree
{
    int N,Record[maxn];
    int mmax[maxn*4],mmin[maxn*4],ssum[maxn*4];
    int lazy[maxn*4],Left,Right,Value;
    void getRecord() // 从 stdin 获取初始值
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++) scanf("%d",&Record[i]);
    }
    void build(int node,int l,int r)
    {
        lazy[node]=0;
        if(l==r)
        {
            mmax[node]=mmin[node]=ssum[node]=Record[l];
            return;
        }
        int mid=(l+r)>>1;
        build(node<<1,l,mid);
        build((node<<1)+1,mid+1,r);
        ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
        mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
        mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
    }
    void pushDown(int node,int l,int r)
    {
        int mid=(l+r)>>1;
        lazy[node<<1]=lazy[(node<<1)+1]=lazy[node];
        ssum[node<<1]=lazy[node]*(mid-l+1);
        ssum[(node<<1)+1]=lazy[node]*(r-mid);
        mmax[node<<1]=mmax[(node<<1)+1]=lazy[node];
        mmin[node<<1]=mmin[(node<<1)+1]=lazy[node];
        lazy[node]=0;
    }
    void Update(int node,int l,int r)
    {
        if(Left<=l&&r<=Right)
        {
            lazy[node]=Value;
            ssum[node]=Value*(r-l+1);
            mmax[node]=mmin[node]=Value;
            return;
        }
        int mid=(l+r)>>1;
        if(lazy[node]) pushDown(node,l,r);
        if(Left<=mid) Update(node<<1,l,mid);
        if(Right>mid) Update((node<<1)+1,mid+1,r);
        ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
        mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
        mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
    }
    int AskMax(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return mmax[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1;
        bool exl=(Left<=mid),exr=(Right>mid);
        if(exl&&exr) return max(AskMax(node<<1,l,mid),AskMax((node<<1)+1,mid+1,r));
        if(exl) return AskMax(node<<1,l,mid); return AskMax((node<<1)+1,mid+1,r);
    }
    int AskMin(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return mmin[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1;
        bool exl=(Left<=mid),exr=(Right>mid);
        if(exl&&exr) return min(AskMin(node<<1,l,mid),AskMin((node<<1)+1,mid+1,r));
        if(exl) return AskMin(node<<1,l,mid); return AskMin((node<<1)+1,mid+1,r);
    }
    int AskSum(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return ssum[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1,ans=0;
        if(Left<=mid) ans+=AskSum(node<<1,l,mid);
        if(Right>mid) ans+=AskSum((node<<1)+1,mid+1,r);
        return ans;
    }
};

void segtree_toolkit()
{
    SGTree ac;
    ac.N = 5;
    for(int i=1;i<=ac.N;i++) ac.Record[i]=1; // 手动设定初始值
    ac.build(1,1,ac.N);

    int Q;scanf("%d",&Q);
    while(Q--)
    {
        scanf("%d %d %d",&ac.Left,&ac.Right,&ac.Value); // ac.Value
        ac.Update(1,1,ac.N);
    }

    auto res = ac.AskMax(1,1,ac.N);
}

} // namespace segment_tree

// 二维线段树，支持区间修改，区间查询
// 代码年久失修 整理时未经测试 仅供参考
namespace segment_tree_2d {

using namespace std;

const int maxn=(1<<20)+100;
struct Line{
    int start,end; Line(int x,int y){this->start=x,this->end=y;}
    inline int Mid(){return (start+end)>>1;}
    inline int Len(){return end+1-start;}
    inline Line left_half(){ return Line(start,this->Mid()); }
    inline Line right_half(){ return Line(this->Mid()+1,end); }
    inline bool IncludePos(int x){ return start<=x&&x<=end; }
    inline bool InlcudeLine(Line x){ return start<=x.start&&x.end<=end; }
    inline bool Intersect(Line x){ return !(start>x.end||end<x.start); }
};
int N,Sum[maxn<<3],_row,_colum,delta;
Line q_row(0,0),q_colum(0,0);
bool avaliable[maxn<<3];
inline int get_son(int node){ return 4*node-2; }
void push_up(int node)
{
    Sum[node]=0;for(int i=0;i<4;i++) if(avaliable[get_son(node)+i]) Sum[node]+=Sum[get_son(node)+i];
}
void bulid(int node,Line row,Line colum)
{
    if(row.Len()<=0||colum.Len()<=0) {avaliable[node]=false; return;}
    avaliable[node]=true; if(row.Len()==1&&colum.Len()==1){ Sum[node]=0;return; }
    bulid(get_son(node)+0,row.left_half(),colum.left_half());
    bulid(get_son(node)+1,row.left_half(),colum.right_half());
    bulid(get_son(node)+2,row.right_half(),colum.left_half());
    bulid(get_son(node)+3,row.right_half(),colum.right_half());
    push_up(node);
}
void update(int node,Line row,Line colum)
{
    if(!avaliable[node]) return ;
    if(!row.IncludePos(_row)||!colum.IncludePos(_colum)) return;
    if(row.Len()==1&&colum.Len()==1){ Sum[node]+=delta; return; }
    if(avaliable[get_son(node)+0]) update(get_son(node)+0,row.left_half(),colum.left_half());
    if(avaliable[get_son(node)+1]) update(get_son(node)+1,row.left_half(),colum.right_half());
    if(avaliable[get_son(node)+2]) update(get_son(node)+2,row.right_half(),colum.left_half());
    if(avaliable[get_son(node)+3]) update(get_son(node)+3,row.right_half(),colum.right_half());
    push_up(node);
}
int ask(int node,Line row,Line colum)
{
    if(!avaliable[node]) return 0;
    if(!row.Intersect(q_row)||!colum.Intersect(q_colum)) return 0;
    if(q_row.InlcudeLine(row)&&q_colum.InlcudeLine(colum)) return Sum[node];
    int ans=0;if(avaliable[get_son(node)+0]) ans+=ask(get_son(node)+0,row.left_half(),colum.left_half());
    if(avaliable[get_son(node)+1]) ans+=ask(get_son(node)+1,row.left_half(),colum.right_half());
    if(avaliable[get_son(node)+2]) ans+=ask(get_son(node)+2,row.right_half(),colum.left_half());
    if(avaliable[get_son(node)+3]) ans+=ask(get_son(node)+3,row.right_half(),colum.right_half());return ans;
}

} // namespace segment_tree_2d