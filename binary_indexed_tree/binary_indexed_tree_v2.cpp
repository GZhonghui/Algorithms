#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdint>
using namespace std;
const int maxn=1024;
typedef int64_t ll;
struct LowBitTree
{   
    // 树状数组求和的区间包括0的话，会出一点小问题，因为lowbit(0) = 0
    // 如果需要包括0的话，可以在Add和Sum的函数内部统一做一个偏移
    ll C[maxn],n;
    void init(ll n=maxn-1) // n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(ll)*maxn);
    }
    ll lowbit(ll x){ return x&(-x); }
    ll Sum(ll pos) // 计算Sum[1,pos]
    {
        ll ans=0;
        for(ll i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(ll pos,ll value) // 在pos的位置增加value
    {
        for(ll i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
};
int main()
{
    return 0;
}