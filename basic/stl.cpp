// C++ STL 演示各种用法
// C++ 14
// g++ stl.cpp -c --std=c++14

#include <algorithm>
#include <iterator> // For std::advance
#include <functional> // 包含 std::hash
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

// AI生成
struct sortable {
    int value;

    // 重载<运算符，定义优先级规则。这里我们定义越小的值优先级越高。
    bool operator<(const sortable& other) const {
        // 注意这里我们返回“大于”逻辑来实现“最小值优先”的逻辑。
        return value > other.value;
    }
};

// AI生成
// unordered set / map内部是使用哈希表实现的，所以需要重载==函数
struct hashable {
    int x;
    double y;

    bool operator==(const hashable& other) const {
        return x == other.x && y == other.y;
    }
};

// 本函数由AI生成
template<typename T>
void vector_demo()
{
    // 初始化为256个0
    std::vector<T> v(256, (T)0);

    // 清空vector
    v.clear(); // []

    // 在末尾添加元素
    v.push_back((T)1); // [1]
    v.push_back((T)2); // [1, 2]
    v.push_back((T)3); // [1, 2, 3]

    // 使用 assign 重新赋值
    v.assign(5, (T)4); // [4, 4, 4, 4, 4]

    // 使用 at 访问元素（安全访问）
    T value_at_2 = v.at(2); // [4, 4, 4, 4, 4] 访问第3个元素

    // 检查容量（容器在不重新分配内存的情况下能容纳的最大元素数）
    size_t cap = v.capacity(); // 通常大于等于 5

    // 使用 emplace 在中间位置直接构造元素
    auto it = v.begin() + 2;
    v.emplace(it, (T)100); // [4, 4, 100, 4, 4, 4]

    // 获取底层数组的直接指针
    T* raw_array = v.data(); // 返回指向 [4, 4, 100, 4, 4, 4] 的指针

    // 在指定位置插入元素
    it = v.begin();
    v.insert(it + 1, (T)10); // [4, 10, 4, 100, 4, 4, 4]

    // 访问特定位置的元素
    T elem_at_index_1 = v[1]; // [4, 10, 4, 100, 4, 4, 4]
    T elem_at_front = v.front(); // [4, 10, 4, 100, 4, 4, 4]
    T elem_at_back = v.back(); // [4, 10, 4, 100, 4, 4, 4]

    // 使用迭代器遍历vector
    for(auto i = v.begin(); i != v.end(); ++i) {
        T _local = *i; // [4, 10, 4, 100, 4, 4, 4]
    }

    // 使用范围for循环遍历vector
    for(const T& _local : v) {
        // [4, 10, 4, 100, 4, 4, 4]
    }

    // 删除末尾的元素
    v.pop_back(); // [4, 10, 4, 100, 4, 4]

    // 修改vector中的元素
    if (!v.empty()) {
        v[0] = (T)100; // [100, 10, 4, 100, 4, 4]
    }

    // 使用下标运算符访问元素
    for(size_t i = 0; i < v.size(); i += 1) {
        T _local = v[i]; // [100, 10, 4, 100, 4, 4]
    }
}

// 本函数由AI生成
template<typename T>
void stack_demo()
{
    std::stack<T> s;

    // 向堆栈添加元素
    s.push((T)1); // 栈顶 > [1]
    s.push((T)2); // 栈顶 > [2, 1]
    s.push((T)3); // 栈顶 > [3, 2, 1]

    // 在栈顶直接构造元素
    s.emplace((T)4); // 栈顶 > [4, 3, 2, 1]

    // 访问栈顶元素
    T top_elem = s.top(); // 栈顶 > [4, 3, 2, 1]

    // 移除栈顶元素
    s.pop(); // 栈顶 > [3, 2, 1]
    s.pop(); // 栈顶 > [2, 1]

    // 创建另一个堆栈并添加元素
    std::stack<T> other_stack;
    other_stack.push((T)5);
    other_stack.push((T)6); // 栈顶 > [6, 5]

    // 交换两个堆栈的内容
    s.swap(other_stack); // s 的栈顶 > [6, 5], other_stack 的栈顶 > [2, 1]

    // 获取堆栈的大小
    size_t size = s.size(); // 栈顶 > [6, 5]

    // 使用底层容器进行操作（这里仅演示操作，实际不推荐这样做）
    T last_elem = s.c.back(); // 直接访问底层容器的最后一个元素，栈顶 > [6, 5]

    // 移除所有元素
    while (!s.empty()) {
        s.pop(); // 迭代移除，直至栈为空
    }

    // 最终栈状态为空
    bool is_empty = s.empty(); // 栈为空
}

// 本函数由AI生成
template<typename T>
void queue_demo()
{
    // 普通队列
    std::queue<T> q;

    // 向普通队列添加元素
    q.push((T)1); // 队尾 > [1]
    q.push((T)2); // 队尾 > [1, 2]
    q.push((T)3); // 队尾 > [1, 2, 3]

    // 访问普通队列的首元素和末尾元素
    T front_q = q.front(); // 队首 > [1]
    T back_q = q.back();  // 队尾 > [3]

    // 移除普通队列的首元素
    q.pop(); // 队尾 > [2, 3]

    // 检查普通队列是否为空
    bool is_empty_q = q.empty(); // 队尾 > [2, 3]

    // 优先队列
    std::priority_queue<T> pq;

    // 向优先队列添加元素
    pq.push((T)1); // 最大元素 > [1]
    pq.push((T)2); // 最大元素 > [2, 1]
    pq.push((T)3); // 最大元素 > [3, 2, 1]

    // 访问优先队列的最大元素
    T top_pq = pq.top(); // 最大元素 > [3]

    // 移除优先队列的最大元素
    pq.pop(); // 最大元素 > [2, 1]

    // 检查优先队列是否为空
    bool is_empty_pq = pq.empty(); // 最大元素 > [2, 1]

    // 双端队列
    std::deque<T> dq;

    // 向双端队列添加元素
    dq.push_back((T)1); // 双端 > [1]
    dq.push_front((T)2); // 双端 > [2, 1]
    dq.push_back((T)3); // 双端 > [2, 1, 3]

    // 使用 at 访问元素
    T at_dq = dq.at(1); // 双端 > [1]

    // 在双端队列中插入元素
    auto it = dq.begin();
    std::advance(it, 2); // 移动到第三个位置
    dq.insert(it, (T)4); // 双端 > [2, 1, 4, 3]

    // 访问双端队列的首尾元素
    T front_dq = dq.front(); // 双端 > [2]
    T back_dq = dq.back();  // 双端 > [3]

    // 使用 erase 删除元素
    it = dq.begin();
    std::advance(it, 1); // 移动到第二个位置
    dq.erase(it); // 双端 > [2, 4, 3]

    // 移除双端队列的首尾元素
    dq.pop_front(); // 双端 > [4, 3]
    dq.pop_back();  // 双端 > [4]

    // 检查双端队列是否为空
    bool is_empty_dq = dq.empty(); // 双端 > [4]
}

// 本函数由AI生成
template<typename T>
void list_demo()
{
    // 创建一个双向链表
    std::list<T> lst;

    // 向链表添加元素
    lst.push_back((T)1);  // 链表 > [1]
    lst.push_back((T)2);  // 链表 > [1, 2]
    lst.push_front((T)3); // 链表 > [3, 1, 2]

    // 在链表中插入元素
    auto it = lst.begin();
    advance(it, 1);  // 移动到链表的第二个元素
    lst.insert(it, (T)4); // 链表 > [3, 4, 1, 2]

    // 使用迭代器访问链表元素
    it = lst.begin();
    T value = *it; // 链表 > [3, 4, 1, 2]，访问第一个元素

    // 删除元素
    it = lst.begin();
    advance(it, 2); // 移动到第三个元素
    lst.erase(it); // 链表 > [3, 4, 2]

    // 使用反向迭代器访问元素
    auto rit = lst.rbegin();
    value = *rit; // 链表 > [3, 4, 2]，访问最后一个元素 (2)

    // 检查链表是否为空
    bool is_empty = lst.empty(); // 链表 > [3, 4, 2]

    // 获取链表的大小
    size_t size = lst.size(); // 链表 > [3, 4, 2]

    // 清空链表
    lst.clear(); // 链表 > []

    // 检查链表是否为空（再次）
    is_empty = lst.empty(); // 链表为空

    // 链表合并操作
    // 创建两个双向链表
    std::list<T> lst1, lst2;

    // 向两个链表添加元素
    lst1.push_back((T)1);
    lst1.push_back((T)3);
    lst1.push_back((T)5);  // 链表 lst1 > [1, 3, 5]
    
    lst2.push_back((T)2);
    lst2.push_back((T)4);
    lst2.push_back((T)6);  // 链表 lst2 > [2, 4, 6]

    // 合并链表，假设两个链表已经按照排序顺序
    lst1.merge(lst2);  // 链表 lst1 > [1, 2, 3, 4, 5, 6], 链表 lst2 > []

    // 验证 lst2 是否为空
    bool is_empty_lst2 = lst2.empty(); // 链表 lst2 为空

    // 继续添加元素
    lst1.push_back((T)7);  // 链表 lst1 > [1, 2, 3, 4, 5, 6, 7]

    // 插入元素到 lst2 并再次合并
    lst2.push_back((T)0);  // 链表 lst2 > [0]
    lst1.merge(lst2);  // 链表 lst1 > [0, 1, 2, 3, 4, 5, 6, 7], 链表 lst2 > []

    // 清空链表 lst1
    lst1.clear(); // 链表 lst1 > []
    
    // 检查链表是否为空
    bool is_empty_lst1 = lst1.empty(); // 链表 lst1 为空
}

template<typename T1, typename T2>
void pair_demo()
{
    pair<T1,T2> p = make_pair((T1)0,(T2)0); // 不显式指定数据类型也可以

    T1 _t1 = p.first; // 引用，不是指针
    T2 _t2 = p.second;
}

// 本函数由AI生成
template<typename T>
void set_demo()
{
    // 有序集合
    std::set<T> s;
    // std::set 保持元素按照特定顺序排序，通常实现为红黑树。
    // 插入、删除和查找操作的时间复杂度为 O(log n)。
    s.insert((T)1); // 集合 s > [1]
    s.insert((T)2); // 集合 s > [1, 2]
    s.insert((T)3); // 集合 s > [1, 2, 3]

    auto found = s.find((T)2); // 查找时间为 O(log n)
    bool exists = (found != s.end()); // exists 为 true

    s.erase((T)2); // 删除时间为 O(log n)，集合 s > [1, 3]

    // 有序多重集合
    std::multiset<T> ms;
    // std::multiset 和 std::set 类似，但允许存储重复元素。
    ms.insert((T)1); // 集合 ms > [1, 1, 2]
    ms.insert((T)1);
    ms.insert((T)2);

    size_t count = ms.count((T)1); // count 为 2

    // 无序集合
    std::unordered_set<T> us;
    // std::unordered_set 不保持元素的顺序，通常实现为哈希表。
    // 提供平均常数时间复杂度的插入、删除和查找操作，但最坏情况下为 O(n)。
    us.insert((T)3); // 集合顺序不定
    us.insert((T)1);
    us.insert((T)2);

    found = us.find((T)3); // 平均查找时间为 O(1)
    exists = (found != us.end()); // exists 为 true

    // 无序多重集合
    std::unordered_multiset<T> ums;
    // std::unordered_multiset 和 std::unordered_set 类似，但允许存储重复元素。
    ums.insert((T)4); // 集合顺序不定
    ums.insert((T)4);
    ums.insert((T)5);

    count = ums.count((T)4); // count 为 2

    // 清空集合
    s.clear(); // 集合 s > []
    ms.clear(); // 集合 ms > []
    us.clear(); // 集合 us > []
    ums.clear(); // 集合 ums > []
}

// 注意！map的key可以使用pair，但是unordered_map的key不能使用pair
// 本函数由AI生成
template<typename T1, typename T2>
void map_demo()
{
    // 有序映射
    std::map<T1, T2> m;
    m.insert({(T1)1, (T2)2}); // 映射 m > {1:2}
    m[(T1)3] = (T2)4;         // 映射 m > {1:2, 3:4}

    auto it = m.find((T1)1);   // 查找键为1的元素
    bool exists = (it != m.end()); // exists 为 true
    T2 value = it->second;     // value 为 2
    m.erase((T1)1);            // 映射 m > {3:4}

    // 有序多重映射
    std::multimap<T1, T2> mm;
    mm.insert({(T1)1, (T2)2}); // 映射 mm > {1:2}
    mm.insert({(T1)1, (T2)3}); // 映射 mm > {1:2, 1:3}
    mm.insert({(T1)1, (T2)4}); // 映射 mm > {1:2, 1:3, 1:4}

    // 遍历键为 1 的所有值
    auto range = mm.equal_range((T1)1); // 获取键为 1 的范围
    for (auto it = range.first; it != range.second; ++it) {
        T2 value_for_key = it->second;  // 遍历键 1 的所有值，value 为 2, 3, 4
    }

    // 无序映射
    std::unordered_map<T1, T2> um;
    um[(T1)5] = (T2)6;         // 映射 um > {5:6}
    um.insert({(T1)7, (T2)8}); // 映射 um > {5:6, 7:8}

    it = um.find((T1)5);       // 查找键为5的元素
    exists = (it != um.end()); // exists 为 true
    value = it->second;        // value 为 6

    // 无序多重映射
    std::unordered_multimap<T1, T2> umm;
    umm.insert({(T1)9, (T2)10}); // 映射 umm > {9:10}
    umm.insert({(T1)9, (T2)11}); // 映射 umm > {9:10, 9:11}
    umm.insert({(T1)9, (T2)12}); // 映射 umm > {9:10, 9:11, 9:12}

    // 遍历键为 9 的所有值
    auto range_umm = umm.equal_range((T1)9); // 获取键为 9 的范围
    for (auto it = range_umm.first; it != range_umm.second; ++it) {
        T2 value_for_key_umm = it->second; // 遍历键 9 的所有值，value 为 10, 11, 12
    }

    // 清空所有映射
    m.clear();   // 映射 m > []
    mm.clear();  // 映射 mm > []
    um.clear();  // 映射 um > []
    umm.clear(); // 映射 umm > []
}

// AI生成
// 为自定义类型 hashable 特化 std::hash
// 显式“实例化”一个模板struct（感觉用词不太恰当）
template<>
struct std::hash<hashable> {
    size_t operator()(const hashable& s) const noexcept {
        // 组合 x 和 y 的哈希值，使用异或和位移来混合哈希
        return std::hash<int>()(s.x) ^ (std::hash<double>()(s.y) << 1);
    }
};

// AI生成
// 演示 std::hash 的用法
void hash_demo() {
    // 基本类型的哈希
    std::hash<int> hash_int; // 这些都可以当作函数来用
    std::hash<double> hash_double;
    std::hash<std::string> hash_string;

    // 自定义类型的哈希
    std::hash<hashable> hash_custom;
}