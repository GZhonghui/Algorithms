/*

树状数组 binary indexed tree (fenwick tree)

树状数组是一种支持 单点修改（只能加减？） 和 区间查询（只能查询和？） 的，代码量小的数据结构。

本文件包括：树状数组，单点加减，求前缀和，速度比线段树快

应用 & 例题：
求逆序对，时间复杂度是$O(N\log{N})$；并且目标区间可以动态维护。
例题：[Another Shuffle Window](https://atcoder.jp/contests/abc380/tasks/abc380_g)

拓展：二维树状数组，支持区间加减和区间查询（注意：代码年代久远，正确性未实际验证过）

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdint>

namespace binary_indexed_tree {

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

} // namespace binary_indexed_tree

// 2D 树状数组，支持区间加减和区间查询
namespace binary_indexed_tree_2d {
using namespace std;

const int maxn=(1<<10)+10;

class Lowbit2D
{
public:
    int row,colum;
    int C1[maxn][maxn],C2[maxn][maxn];
    int C3[maxn][maxn],C4[maxn][maxn];
public:
    // 下标范围是[1,n] & [1,m]，下述的操作也都是闭区间
    // x 属于 [1,n]，y 属于 [1,m]
    void init(int n,int m)
    {
        this->row=n;this->colum=m;
        memset(C1,0,sizeof(C1));memset(C2,0,sizeof(C2));
        memset(C3,0,sizeof(C3));memset(C4,0,sizeof(C4));
    }
    void range_add(int x1,int y1,int x2,int y2,int x)
    {
        add(x1,y1,x);
        add(x1,y2+1,-x);
        add(x2+1,y1,-x);
        add(x2+1,y2+1,x);
    }
    int range_ask(int x1,int y1,int x2,int y2)
    {
        return ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
    }
protected:
    int lowbit(int x){return x&(-x);}

    void add(int x,int y,int val)
    {
        for(int i=x;i<=row;i+=lowbit(i))
        for(int j=y;j<=colum;j+=lowbit(j))
        {
            C1[i][j]+=val;
            C2[i][j]+=val*x;
            C3[i][j]+=val*y;
            C4[i][j]+=val*x*y;
        }
    }
    int ask(int x,int y)
    {
        int ret=0;
        for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
        {
            ret+=(x+1)*(y+1)*C1[i][j]+C4[i][j];
            ret-=(y+1)*C2[i][j]+(x+1)*C3[i][j];
        }
        return ret;
    }
};

} // namespace binary_indexed_tree_2d