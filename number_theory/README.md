## 数论

- bit_operations 比特操作
- breakdown_to_prime_factor 质因数分解
- catalan_number 卡特兰数
- combination 组合数
- euclidean_algorithm 欧几里得算法 辗转相除法
- euler_quick_power (自己取的名字) 欧拉降幂
- eulers_totient_function 欧拉函数
- inverse_element 逆元
- permutation 排列
- quick_power 快速幂
- sieve_theory 筛法

## 分数如何取模
求：$R = \frac{P}{Q} \pmod{998244353}$  
做法是求解模线性方程：  
$R \times Q \equiv P \pmod{998244353}$  
$R \equiv P \times Q^{-1} \pmod{998244353}$  
可以看出：只要算出$Q$的逆元就可以了；$P$在计算过程中是可以取模的  
例题：[Another Shuffle Window](https://atcoder.jp/contests/abc380/tasks/abc380_g)