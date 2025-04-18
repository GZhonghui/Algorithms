/*

euler_quick_power (自己取的名字) 欧拉降幂
TODO: 继续整理 暂时还不能用

*/

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int Num,Cnt;
int get_phi(int n)
{
    int ans=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            ans-=ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n!=1) ans-=ans/n;
    return ans;
}
int pow_mod(int a,int k,int mod)
{
    if(k==0) return 1;
    if(a<=1) return a;
    bool if_over = false;
    long long k1=1;
    for(int i=0;i<k;i++)
    {
        k1=k1*a;
        if(k1>=mod)
        {
            if_over=true;
            break;
        }
    }
    int ans=1;
    while(k)
    {
        if(k&1)
        {
            ans*=a;ans%=mod;
        }
        a*=a;a%=mod;k>>= 1;
    }
    if(if_over) ans+=mod;
    return ans;
}
int dfs(int x,int p)
{
    if(x>=Cnt) return Num;
    if(p==1) return 1;
    return pow_mod(Num,dfs(x+1,get_phi(p)),p);
}