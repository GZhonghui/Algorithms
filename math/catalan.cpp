/*

catalan_number 卡特兰数

*/

#include <iostream>
#include <cstdint>

namespace catalan_number {
using namespace std;
using ll = int64_t;

void calc(ll n, vector<ll> &ans) {
    ans.resize(n + 1);
    ans[0] = 1;

    for(ll i = 1; i <= n; i++) {
        ans[i] = ans[i-1] * (4 * i - 2) / (i + 1);
    }
}

} // namespace catalan_number