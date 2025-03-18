/*

二分查找范围

*/

#include <algorithm>
#include <cstdint>

typedef int64_t ll;

// AI生成
// 功能描述：
// 现有一个数组x，[1,n]的下标范围内有n个数字，并且这n个数字已经排好顺序（升序）
// 现在给出一个范围[l,r]
// 在x数组中找到最长的一段范围[a,b]，使得这段范围内的数字（x[a],x[a+1]...x[b]）都在[l,r]内
// 返回a和b的值
std::pair<ll, ll> find_range_ai(ll* x, ll n, ll l, ll r) {
    // 注意调整指针来适应从1开始的下标
    ll* start = std::lower_bound(x + 1, x + n + 1, l);
    ll* end = std::upper_bound(x + 1, x + n + 1, r);

    // 由于 upper_bound 返回的是第一个大于目标的元素位置，需要向前移动一位
    if (end != (x + 1)) {
        --end;
    }

    // 检查找到的区间是否有效（即确保 start <= end）
    if (start > end || *start < l || *end > r) {
        return std::make_pair(-1, -1);  // 返回无效区间
    }

    // 返回区间的下标，数组下标已经从1开始
    return std::make_pair(static_cast<ll>(start - x), static_cast<ll>(end - x));
}