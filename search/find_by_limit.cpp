/*

使用二分查找来查找数组中小于等于 K 的元素数量

*/

#include <algorithm>
#include <vector>

using namespace std;

// 使用二分查找来查找数组中小于等于 K 的元素数量
int countLessThanOrEqualToK(const vector<int>& sortedArray, int K) {
    // 使用 std::upper_bound 来找到第一个大于 K 的元素的索引
    auto it = upper_bound(sortedArray.begin(), sortedArray.end(), K);
    
    // 返回小于等于 K 的元素个数，即 it - sortedArray.begin()
    return it - sortedArray.begin();
}

// 查找大于 K 的元素的个数：N-[上面的结果]就可以了