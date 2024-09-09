#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1024; // 注意数据范围，是否需要int64
struct Quick_C
{
    int Jc[maxn],mod; // Jc是阶乘的意思，可以预先计算
    void pre_cal()
    {
        Jc[0]=Jc[1]=1;
        for(int i=2;i<maxn;i++)
            Jc[i]=Jc[i-1]*i%mod;
    }
    void exgcd(int a,int b,int &x,int &y)
    {
        if(!b) x=1,y=0;
        else
        {
            exgcd(b,a%b,y,x);
            y-=x*(a/b);
        }
    }
    int niYuan(int a,int b)
    {
        int x,y;
        exgcd(a,b,x,y);
        return (x+b)%b;
    }
    int cal_C(int a,int b) // a >= b C_{a}^{b}
    {
        return Jc[a]*niYuan(Jc[b],mod)%mod*niYuan(Jc[a-b],mod)%mod;
    }
};
int main()
{
    return 0;
}
