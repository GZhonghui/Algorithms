/*

斐波那契博弈

有一堆物品，数量为n，两人轮流取，先手第一次可以取任意个但不能全部取完。  
之后每次取的数量必须大于等于1 且小于等于上次（上次？应该指的是对手吧）取的数量的两倍，最后把物品全部取完者胜利

n 为斐波那契数（出现在斐波那契数列中的数字）时，为必败状态

代码来源：https://www.cnblogs.com/tttkf/p/15895646.html

*/

#include <algorithm>
#include <cstdint>
#include <unordered_set>

namespace fibonacci {

using namespace std;
using ll = int64_t;

unordered_set<ll> s;

bool win(ll x) {
    static bool inited = false;
    if(!inited) {
        ll f1 = 1, f2 = 1;
        for(int i = 3; i <= 85; i++) {
            ll f3 = f2 + f1;
            s.insert(f3);
            swap(f1, f2), swap(f2, f3);
        }
        inited = true;
    }
    return !s.count(x);
}

} // namespace fibonacci