/*

树状数组 binary indexed tree

树状数组是一种支持 单点修改（只能加减？） 和 区间查询（只能查询和？） 的，代码量小的数据结构。

本文件包括：树状数组，单点加减，求前缀和，速度比线段树快

应用 & 例题：
求逆序对，时间复杂度是$O(N\log{N})$；并且目标区间可以动态维护。
例题：[Another Shuffle Window](https://atcoder.jp/contests/abc380/tasks/abc380_g)

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdint>

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