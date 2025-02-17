/*

## 筛法 sieve_theory
sieve_theory 筛法

### 埃拉托斯特尼筛法 Eratosthenes
比线性筛慢

### 欧拉筛（线性筛法）
*euler_sieve.cpp*  
线性时间复杂度

### 杜教筛

### 习题
- https://atcoder.jp/contests/typical90/tasks/typical90_ad

*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <vector>

namespace number_theory {

using namespace std;
typedef int64_t ll;
const ll maxn = 1e6 + 10; // 要筛的范围

struct Sieve
{
    bool check[maxn]; // 被check标记的（check[i] == true）都是非质数（not_prime）
    vector<ll> prime; // 找到的质数

    void init()
    {
        memset(check,0,sizeof(check));
        prime.clear();
    }
    void calc(ll n) // 找到[,n]以内的质数
    {
        for(ll i=2;i<=n;i++)
        {
            if(!check[i]) prime.push_back(i);
            for(ll j=0;j<prime.size();j++)
            {
                if(i*prime[j]>n) break;
                check[i*prime[j]]=true;
                if(i%prime[j]==0) break;
            }
        }
    }
};

} // NAMESPACE number_theory