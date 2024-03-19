// https://vjudge.net/problem/HDU-1698
// https://acm.hdu.edu.cn/showproblem.php?pid=1698 Just a Hook

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100010;
struct SGTree
{
    int N,Record[maxn];
    int mmax[maxn*4],mmin[maxn*4],ssum[maxn*4];
    int lazy[maxn*4],Left,Right,Value;
    void getRecord()
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
}ac;
int main()
{
    //freopen("in.txt","r",stdin);
    int T,Case=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&ac.N);
        for(int i=1;i<=ac.N;i++) ac.Record[i]=1;
        ac.build(1,1,ac.N);
        int Q;scanf("%d",&Q);
        while(Q--)
        {
            scanf("%d %d %d",&ac.Left,&ac.Right,&ac.Value);
            ac.Update(1,1,ac.N);
        }
        printf("Case %d: The total value of the hook is %d.\n",++Case,ac.ssum[1]);
    }
    return 0;
}