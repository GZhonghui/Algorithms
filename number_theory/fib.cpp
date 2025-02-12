#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>

// 可以参考这里 fib数列的性质 以下模板代码也参考了这里的内容
// https://oi-wiki.org/math/combinatorics/fibonacci/

namespace fib {
    using namespace std;
    typedef int64_t ll;

    // 定义
    // fib_0 = 0, fib_1 = 1

    // 朴素算法 注意数据范围
    // int64的上限大约是9e18 而fib_90就能到达这个数量级
    ll fib(ll n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        return fib(n - 1) + fib(n - 2);
    }

    // fib_n有解析解 只是计算需要很高的精度 一般不用

    // 因为fib数列增长很快
    // 所以在不取模数的情况下快速计算是没有意义的
    // 就算能计算也存不下
    // 这里是使用「快速倍增法」进行计算
    // 还有另一种方法是「矩阵乘法」 只是常数较大
    pair<ll, ll> quick_fib(ll n, ll mod) { // return {fib_n, fib_(n+1)}
        if (n == 0) return make_pair<ll, ll>(0, 1);
        pair<ll, ll> p = quick_fib(n >> 1, mod);
        int c = p.first * (2 * p.second - p.first) % mod;
        int d = (p.first * p.first + p.second * p.second) % mod;
        if (n & 1)
            return make_pair<ll, ll>(d, (c + d) % mod);
        else
            return make_pair<ll, ll>(c, d);
    }

    // fib数列可以用于编码
    // 任何自然数 n 可以被唯一地表示成一些斐波那契数的和

    // 在模意义下的fib数列一定是有周期性的 参照「Pisano periods」
    // 当然 这个周期由模数决定
    // 这里计算的不一定是最小周期
    ll get_cycle_from_mod(ll mod) {
        return 0; // TODO
    }
} // namespace fib