/*

背包问题一般是刚开始学习DP的时候接触到的第一个问题
所以一些关于DP 通用的思考方式和技巧 也记录在这里

1. 如何处理环？  
延长1倍，变成2n的长度

2. 记忆化搜索  
在求解动态规划的问题时，记忆化搜索和递推，都确保了同一状态至多只被求解一次
而它们实现这一点的方式则略有不同：
递推通过设置明确的访问顺序来避免重复访问
记忆化搜索虽然没有明确规定访问顺序，但通过给已经访问过的状态打标记的方式，也达到了同样的目的
我个人非常喜欢用记忆化搜索 写起来非常得清晰

==========

背包问题 knapsack problem

01背包
完全背包
多重背包
混合背包

2维费用
分组背包
依赖关系
泛化物品

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <climits>
#include <cstring>
#include <vector>

namespace knapsack_problem {
    typedef int64_t ll;
    const ll inf = INT64_MAX;

    // 此代码尚未经过检验
    // [1,n], 1-indexed
    // 01背包 + 完全背包 + 多重背包 = 混合背包
    // n 个物品，重量上限为 weight_limit，求解可能的最大价值
    // 第 i 个物品的重量为 weights[i]，价值为 values[i]，数量为 counts[i]（count == -1 表示有无穷个）
    ll max_value(ll n, ll weight_limit, ll* weights, ll* values, ll* counts)
    {
        ll ans = 0, dp[weight_limit + 8];
        memset(dp, 0, sizeof(ll)*(weight_limit + 8));

        std::vector<ll> local_weights, local_values, local_counts;
        for(ll i=1; i<=n; i+=1)
        {
            if(counts[i] == -1 || counts[i] == 1)
            {
                local_weights.push_back(weights[i]);
                local_values.push_back(values[i]);
                local_counts.push_back(counts[i]);
            }else if(counts[i] > 1)
            {
                ll this_count = counts[i], now_count = 1;

                while(this_count)
                {
                    if(this_count & 1)
                    {
                        local_weights.push_back(weights[i] * now_count);
                        local_values.push_back(values[i] * now_count);
                        local_counts.push_back(1);
                    }

                    this_count >>= 1;
                    now_count <<= 1;
                }
            }
        }

        for(ll i=0, _size=(ll)local_weights.size(); i<_size; i+=1)
        {
            if(local_counts[i] == 1)
            {
                for(ll j=weight_limit; j>=local_weights[i]; j-=1)
                {
                    dp[j] = std::max(dp[j], dp[j - local_weights[i]] + local_values[i]);
                }
            }else if(local_counts[i] == -1)
            {
                for(ll j=local_weights[i]; j<=weight_limit; j+=1)
                {
                    dp[j] = std::max(dp[j], dp[j - local_weights[i]] + local_values[i]);
                }
            }
        }

        return ans = dp[weight_limit];
    }

    // 此代码尚未经过检验
    // 有 n 个物品，范围[1,n]，第 i 个物品的重量为 weights[i]，价值为 values[i]
    // ans[0, value_limit]为结果 ans[i]表示选择的物品价值总和为i的时候，最小的质量和为ans[i]
    void min_weight(ll n, ll value_limit, ll* weights, ll* values, ll* ans)
    {
        for(ll i=1; i<=value_limit; i+=1)
        {
            ans[i] = inf;
        }
        ans[0] = 0;

        for(ll i=1; i<=n; i+=1)
        {
            for(ll j=value_limit; j>=1; j-=1)
            {
                if(j >= values[i] && ans[j - values[i]] < inf && ans[j - values[i]] + weights[i] < ans[j])
                {
                    ans[j] = ans[j - values[i]] + weights[i];
                }
            }
        }
    }

    // 此份代码尚未经过验证
    // 物品范围[1,n]，第 i 个物品的重量为 weights_1[i] 和 weights_2[i]，价值为 values[i]
    // 两个重量都要在各自的限制内 求解可能的最大价值
    ll max_value_2d(ll n, ll weight_limit_1, ll* weights_1, ll weight_limit_2, ll* weights_2, ll* values)
    {
        ll dp[weight_limit_1 + 4][weight_limit_2 + 4];
        for(ll i=1; i<=n; i+=1)
        {
            for(ll j=weight_limit_1; j>=weights_1[i]; j-=1)
            {
                for(ll k=weight_limit_2; k>=weights_2[i]; k-=1)
                {
                    dp[j][k] = std::max(dp[j][k], dp[j-weights_1[i]][k-weights_2[i]] + values[i]);
                }
            }
        }

        return dp[weight_limit_1][weight_limit_2];
    }
} // namespace knapsack_problem