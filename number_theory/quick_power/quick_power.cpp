#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<iostream>

const uint64_t mod = 1e9+7;

uint64_t pow(uint64_t base, uint64_t times)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    uint64_t ans = pow(base, times>>1) % mod;
    
    ans = ans * ans % mod;
    if(times % 2) ans = ans * base % mod;

    return ans;
}