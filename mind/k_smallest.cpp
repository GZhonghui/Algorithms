/*

k_smallest 维护最小的k个数

*/

#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>
#include <functional> // 用于 greater<int>

namespace k_smallest {
typedef int64_t ll;

// 本代码由AI生成，未经测试
// 算法很简单，参考一下就行
class KSmallestSum {
private:
    std::priority_queue<int> maxHeap; // 最大堆
    int k;
    ll sum; // 存储最小 K 个数的和，用 i64 防止溢出

public:
    KSmallestSum(int k) : k(k), sum(0) {}

    void add(int num) {
        if (maxHeap.size() < k) {
            // 如果堆内元素还不足 K 个，直接添加
            maxHeap.push(num);
            sum += num;
        } else {
            // 如果堆已满且新元素小于堆顶元素，则替换
            if (num < maxHeap.top()) {
                sum += num - maxHeap.top();
                maxHeap.pop();
                maxHeap.push(num);
            }
        }
    }

    ll getSum() const {
        return sum;
    }
};

void toolkit() {
    int k = 3;
    KSmallestSum kSmallest(k);
    std::vector<int> nums = {5, 1, 9, 3, 7, 6, 2};

    for (int num : nums) {
        kSmallest.add(num);
        std::cout << "Current sum of smallest "
            << k << " elements: " << kSmallest.getSum() << std::endl;
    }
}

} // namespace k_smallest