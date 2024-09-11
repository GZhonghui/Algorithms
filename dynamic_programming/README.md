# 动态规划

- digit_dp 数位DP 桁DP
- knapsack_problem 背包问题
- longest_common_subsequence 最长公共子序列
- longest_increasing_subsequence 最长上升（不下降）子序列

## Tips

如何处理环？  
延长1倍，变成2n的长度

记忆化搜索  
> 在求解动态规划的问题时，记忆化搜索和递推，都确保了同一状态至多只被求解一次。而它们实现这一点的方式则略有不同：递推通过设置明确的访问顺序来避免重复访问，记忆化搜索虽然没有明确规定访问顺序，但通过给已经访问过的状态打标记的方式，也达到了同样的目的。