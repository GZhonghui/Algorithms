/*

eulers_totient_function 欧拉函数
## 欧拉函数
欧拉总计函数，或者φ函数

TODO: 继续整理

*/

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
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