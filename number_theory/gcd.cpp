/*

euclidean algorithm 欧几里得算法（辗转相除法）
用于求最大公因数和最小公倍数

*/

#include <algorithm>
#include <cstdint>

namespace gcd {
typedef int64_t ll;

// 最大公約数
ll gcd(ll x, ll y)
{
    return y ? gcd(y, x % y) : x;
}

// 最小公倍数
ll lcm(ll x, ll y)
{
    ll g = gcd(x, y);
    return x / g * y;
}

// 拓展欧几里得算法
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

} // namespace gcd