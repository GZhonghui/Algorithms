// 使用 Cursor Composer 生成
// 使用 C++ 17 以上

#include <iostream>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

// S_both 结构体用于表示线段树的每个节点维护的信息
// sum: 维护区间内所有元素的总和
// max: 维护区间内元素的最大值
// len: 维护当前区间的长度,用于区间修改时计算总和
struct S_both {
    long long sum;    // 区间和
    long long max;    // 区间最大值
    int len;         // 区间长度
};

// F_both 结构体用于表示懒标记信息
// add: 懒标记中的加法值,表示要给区间中每个数都加上的值
// set: 懒标记中的设置值,表示要将区间中的数都设置成的值
// is_set: 标记当前操作是加法还是设置操作
//         true表示设置操作,false表示加法操作
//         用于区分两种不同的修改操作
struct F_both {
    long long add;   // 加法值
    long long set;   // 设置值
    bool is_set;     // 是否是设置操作
};

// 定义合并操作
S_both op_both(S_both a, S_both b) {
    return S_both{
        a.sum + b.sum,                    // 区间和的合并
        std::max(a.max, b.max),           // 区间最大值的合并
        a.len + b.len                     // 区间长度的合并
    };
}

// 定义默认值
S_both e_both() {
    return S_both{0, (long long)-1e18, 0};
}

// 修改映射操作
S_both mapping_both(F_both f, S_both s) {
    if (f.is_set) {
        // 如果是设置操作
        return S_both{
            f.set * s.len,        // 所有值都设为set值
            f.set,                // 最大值就是set值
            s.len
        };
    } else {
        // 如果是加法操作
        return S_both{
            s.sum + f.add * s.len,
            s.max + f.add,
            s.len
        };
    }
}

// 修改懒标记合并操作
// 用于将两个懒标记合并为一个懒标记
// 如果f是设置操作，直接覆盖之前的操作
// 如果g是设置操作，在设置后再加上f.add
// 如果两个都是加法操作，直接相加
F_both composition_both(F_both f, F_both g) {
    if (f.is_set) {
        return f;
    } else if (g.is_set) {
        return F_both{f.add, g.set + f.add, true};
    } else {
        // 两个都是加法操作，直接相加
        return F_both{f.add + g.add, 0, false};
    }
}

// 修改懒标记默认值
// 用于表示默认的懒标记
// 默认是加0的操作
F_both id_both() {
    return F_both{0, 0, false};
}

int main() {
    cout << "=== Range Sum and Maximum Demo ===" << endl;
    
    // 初始化一个长度为8的数组
    vector<S_both> initial(8, {0, 0, 1});  // 初始值：和为0，最大值为0，长度为1
    lazy_segtree<S_both, op_both, e_both, F_both, mapping_both, composition_both, id_both> seg(initial);
    
    // 设置一些初始值
    cout << "Set initial values" << endl;
    seg.set(1, {5, 5, 1});  // 位置1设置为5
    seg.set(3, {8, 8, 1});  // 位置3设置为8
    seg.set(5, {3, 3, 1});  // 位置5设置为3
    
    // 查询区间[2,6)的信息
    auto result = seg.prod(2, 6);
    cout << "Query range [2,6):" << endl;
    cout << "Sum: " << result.sum << endl;
    cout << "Max: " << result.max << endl;
    
    // 对区间[1,5)执行+3操作
    cout << "\nAdd 3 to range [1,5)" << endl;
    seg.apply(1, 5, F_both{3});

    // 对区间[2,4)执行设置为10的操作
    cout << "\nSet range [2,4) to 10" << endl;
    seg.apply(2, 4, F_both{10, 0, true});
    
    // 再次查询区间[2,6)的信息
    result = seg.prod(2, 6);
    cout << "Query range [2,6) again:" << endl;
    cout << "Sum: " << result.sum << endl;
    cout << "Max: " << result.max << endl;
    
    // 演示max_right功能
    cout << "\n=== max_right Demo ===" << endl;
    int left = 2; // 从位置2开始
    // check函数需要是单调的，否则会出错
    auto check1 = [](S_both x) { return x.max <= 11; }; // 查找最大值不超过11的最右边界
    int right = seg.max_right(left, check1);
    cout << "Starting from position " << left << ", rightmost position where max <= 11 is: " << right << endl;
    
    // min_left 功能
    cout << "\n=== min_left Demo ===" << endl;
    left = 6; // 从位置6开始
    auto const check = [](S_both x) { 
        if (x.len == 0) return true;  // 处理空区间 g(e()) = true 必须满足
        return x.max >= 3; 
    };
    right = seg.min_left(left, check);
    cout << "Starting from position " << left << ", leftmost position where max >= 3 is: " << right << endl;

    return 0;
}