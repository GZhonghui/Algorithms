/*

线段树 自己实现的版本 有 lazy 标记
修改支持：修改为定值；查询支持：Min、Max、Sum

例题推荐：
https://vjudge.net/problem/HDU-1698
https://vjudge.net/problem/POJ-3237#google_vignette
https://acm.hdu.edu.cn/showproblem.php?pid=1698 Just a Hook
https://atcoder.jp/contests/typical90/tasks/typical90_ac
https://codeforces.com/gym/102566/problem/F Magic Wand
http://poj.org/problem?id=3237 Tree

*/

#include <iostream>
#include <cstdio>
#include <algorithm>

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