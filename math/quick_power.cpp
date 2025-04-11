/*

# 快速幂
quick_power

*/

#include <algorithm>
#include <cstdint>

uint64_t pow(uint64_t base, uint64_t times, uint64_t mod = 1e9+7)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    uint64_t ans = pow(base, times>>1, mod) % mod;
    
    ans = ans * ans % mod;
    if(times & 1) ans = ans * base % mod;

    return ans;
}

// 来源：OI-Wiki，p是模数
int qpow(long long a, int b, long long p) {
  int ans = 1;
  a = (a % p + p) % p;
  for (; b; b >>= 1) {
    if (b & 1) ans = (a * ans) % p;
    a = (a * a) % p;
  }
  return ans;
}