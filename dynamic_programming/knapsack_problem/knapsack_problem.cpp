#include <algorithm>
#include <iostream>
#include <cstdint>
#include <climits>
#include <cstring>
#include <vector>

namespace g
{
    typedef int64_t ll;
    const ll inf = INT64_MAX;

    // 此代码尚未经过检验
    // [1,n]
    // count == -1 表示有无穷个
    // 01背包 + 完全背包 + 多重背包 = 混合背包
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
    // ans[0, value_limit] 选择的物品价值总和为i的时候，最小的质量和为ans[i]
    // 物品范围[1,n]
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
}

int main()
{

    return 0;
}