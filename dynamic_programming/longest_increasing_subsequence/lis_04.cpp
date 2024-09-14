#include <algorithm>
#include <vector>

// 自己写的版本
// todo 求lis的下标序列
// numbers[0,numbers_count)
int lis(int numbers_count, int* numbers, int* dp, bool allow_equal = true)
{
    int buffer[numbers_count + 1];
    buffer[0] = 1, buffer[1] = numbers[0], dp[0] = 1;

    for(int i = 1; i < numbers_count; i += 1)
    {
        int index = allow_equal
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

// AI生成
int lis_ai(int numbers_count, int* numbers, std::vector<int>& lis_index, bool allow_equal = true)
{
    if (numbers_count == 0) return 0;

    std::vector<int> tails(numbers_count, 0);  // 存储最小的结尾元素
    std::vector<int> prev(numbers_count, -1);  // 存储前驱元素的索引
    int length = 0;

    for (int i = 0; i < numbers_count; ++i)
    {
        // 选择upper_bound或lower_bound来确定插入位置
        auto it = allow_equal ? std::upper_bound(tails.begin(), tails.begin() + length, numbers[i])
                              : std::lower_bound(tails.begin(), tails.begin() + length, numbers[i]);

        int index = it - tails.begin();
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
    for (int i = lis_index[length - 1]; i >= 0; i = prev[i]) {
        lis_index[length - 1] = i;
        length--;
    }

    return lis_index.size();  // 返回LIS的长度
}

int main()
{
    return 0;
}