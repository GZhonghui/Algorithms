/*

longest_increasing_subsequence 最长上升（不下降）子序列

子序列和子串
子串（Substring）：原序列中【必须连续】的一段
子序列（Subsequence）：原序列中【可以不连续】的一段
注意：无论是子串和子序列，元素的顺序都是原序列中的顺序

常规思路
dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度  
一维dp数组，思路简单，遍历两遍即可，时间复杂度：$O(N^2)$

优化：二分查找
优化后的时间复杂度：$O(N\log{N})$，思路查看Wiki

例题
https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_h
https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_x

*/

#include <algorithm>
#include <cstdint>
#include <vector>

namespace longest_increasing_subsequence {
using ll = int64_t;

// 自己写的版本
// todo 求lis的下标序列（哪些元素组成了lis）
// numbers[0,numbers_count) 0-indexed（注意）
// dp[i] 表示以 numbers[i] 结尾的最长递增子序列的长度
// allow_equal 表示是【严格上升】还是【不下降】
ll lis(ll numbers_count, ll *numbers, ll *dp, bool allow_equal = true)
{
    ll buffer[numbers_count + 1];
    buffer[0] = 1, buffer[1] = numbers[0], dp[0] = 1;

    for(ll i = 1; i < numbers_count; i += 1)
    {
        // 使用lower_bound还是upper_bound，区别在于是“严格上升”还是“不下降”
        ll index = allow_equal
            ?std::upper_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1
            :std::lower_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1;
        if(index >= buffer[0])
        {
            buffer[0] += 1;
            buffer[buffer[0]] = numbers[i];
        }else
        {
            buffer[index+1] = numbers[i];
        }
        dp[i] = index + 1;
    }

    return buffer[0];
}

// AI生成的模板
// numbers[0,numbers_count) 0-indexed（注意）
// lis_index 存储了lis的下标序列
// allow_equal 表示是【严格上升】还是【不下降】
ll lis_ai(ll numbers_count, ll *numbers, std::vector<ll> &lis_index, bool allow_equal = true)
{
    if (numbers_count == 0) return 0;

    std::vector<ll> tails(numbers_count, 0);  // 存储最小的结尾元素
    std::vector<ll> prev(numbers_count, -1);  // 存储前驱元素的索引
    ll length = 0;

    for (ll i = 0; i < numbers_count; ++i)
    {
        // 选择upper_bound或lower_bound来确定插入位置
        auto it = allow_equal ? std::upper_bound(tails.begin(), tails.begin() + length, numbers[i])
                              : std::lower_bound(tails.begin(), tails.begin() + length, numbers[i]);

        ll index = it - tails.begin();
        tails[index] = numbers[i];
        // 记录前驱元素的索引
        if (index > 0) {
            prev[i] = lis_index[index - 1];
        }
        // 更新当前元素的索引在lis_index中的位置
        if (index == length) {
            lis_index.push_back(i);
            length++;
        } else {
            lis_index[index] = i;
        }
    }

    // 根据prev数组回溯LIS
    for (ll i = lis_index[length - 1]; i >= 0; i = prev[i]) {
        lis_index[length - 1] = i;
        length--;
    }

    return lis_index.size();  // 返回LIS的长度
}

} // namespace longest_increasing_subsequence