/*

combination 组合数（快速组合数计算）

*/

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <algorithm>

namespace combination {
using namespace std;
using ll = int64_t;

const ll maxn = 1024; // 组合数的参数的范围

struct Quick_C
{
protected:
    ll Jc[maxn],mod; // Jc是阶乘的意思，可以预先计算
    void pre_cal()
    {
        Jc[0]=Jc[1]=1;
        for(ll i=2;i<maxn;i++)
            Jc[i]=Jc[i-1]*i%mod;
    }
    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) x=1,y=0;
        else
        {
            exgcd(b,a%b,y,x);
            y-=x*(a/b);
        }
    }
    ll niYuan(ll a,ll b) // 逆元
    {
        ll x,y;
        exgcd(a,b,x,y);
        return (x+b)%b;
    }

public:
    void init(ll mod) // 模数需要是质数
    {
        this->mod=mod;
        pre_cal();
    }
    ll cal_C(ll a,ll b) // a >= b C_{a}^{b} 从a个物品中选择b个的方案数
    {
        return Jc[a]*niYuan(Jc[b],mod)%mod*niYuan(Jc[a-b],mod)%mod;
    }
};

} // namespace combination