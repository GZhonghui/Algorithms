/*

带了懒标记的线段树 可以完全替代普通线段树 更快、支持的操作更多

atcoder_lazysegtree
AtCoder 的 lazysegtree 模板使用指南
AtCoder 的 lazysegtree 写得最优雅，已经加入到 PlayGround 的标准模板中，是最推荐用的一个版本

oi_wiki_seg
oi-wiki 的 lazysegtree 模板使用指南
可以区间加/求和的线段树模板 & 可以区间修改/求和的线段树模板

*/

#include <iostream>
#include <atcoder/lazysegtree>

// 使用 Cursor Composer 生成
// 使用 C++ 17 以上
namespace atcoder_lazysegtree {
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
// 不是代表一个基本单位（len = 1），而是一个空区间（len = 0）
S_both e_both() {
    return S_both{0, (long long)-1e18, 0};
}

// 修改映射操作
// 将懒标记应用到线段树的节点上
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
F_both composition_both(F_both new_op, F_both old_op) {
    if (new_op.is_set) {
        return new_op;
    } else if (old_op.is_set) {
        return F_both{old_op.add, old_op.set + new_op.add, true};
    } else {
        // 两个都是加法操作，直接相加
        return F_both{old_op.add + new_op.add, 0, false};
    }
}

// 修改懒标记默认值
// 用于表示默认的懒标记
// 默认是加0的操作
F_both id_both() {
    return F_both{0, 0, false};
}

int atcoder_lazysegtree_test() {
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
    
    // 注意：以下两个二分查找函数，要再详细确认一下是否正确

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

} // namespace atcoder_lazysegtree

// 代码来源：https://oi-wiki.org/ds/seg/
namespace oi_wiki_seg {
using namespace std;

// 区间加/求和
template <typename T>
class SegTreeLazyRangeAdd {
    vector<T> tree, lazy;
    vector<T> *arr;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && lazy[p]) {
            lazy[p * 2] += lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            tree[p * 2] += lazy[p] * (cm - cl + 1);
            tree[p * 2 + 1] += lazy[p] * (cr - cm);
            lazy[p] = 0;
        }
    }

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
        if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }

    void range_add(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            lazy[p] += val;
            tree[p] += (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_add(l, r, val, cl, m, p * 2);
        if (r > m) range_add(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = (*arr)[s];
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    explicit SegTreeLazyRangeAdd<T>(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    void show(int p, int depth = 0) {
        if (p > n4 || tree[p] == 0) return;
        show(p * 2, depth + 1);
        for (int i = 0; i < depth; ++i) putchar('\t');
        printf("%d:%d\n", tree[p], lazy[p]);
        show(p * 2 + 1, depth + 1);
    }

    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

    void range_add(int l, int r, T val) { range_add(l, r, val, 0, end, root); }
};

// 区间修改/求和
template <typename T>
class SegTreeLazyRangeSet {
    vector<T> tree, lazy;
    vector<T> *arr;
    vector<bool> ifLazy;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && ifLazy[p]) {
            lazy[p * 2] = lazy[p],ifLazy[p*2] = 1;
            lazy[p * 2 + 1] = lazy[p],ifLazy[p*2+1] = 1;
            tree[p * 2] = lazy[p] * (cm - cl + 1);
            tree[p * 2 + 1] = lazy[p] * (cr - cm);
            lazy[p] = 0;
            ifLazy[p] = 0;
        }
    }

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) return tree[p];
        int m = cl + (cr - cl) / 2;
        T sum = 0;
        maintain(cl, cr, p);
        if (l <= m) sum += range_sum(l, r, cl, m, p * 2);
        if (r > m) sum += range_sum(l, r, m + 1, cr, p * 2 + 1);
        return sum;
    }

    void range_set(int l, int r, T val, int cl, int cr, int p) {
        if (l <= cl && cr <= r) {
            lazy[p] = val;
            ifLazy[p] = 1;
            tree[p] = (cr - cl + 1) * val;
            return;
        }
        int m = cl + (cr - cl) / 2;
        maintain(cl, cr, p);
        if (l <= m) range_set(l, r, val, cl, m, p * 2);
        if (r > m) range_set(l, r, val, m + 1, cr, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = (*arr)[s];
            return;
        }
        int m = s + (t - s) / 2;
        build(s, m, p * 2);
        build(m + 1, t, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    explicit SegTreeLazyRangeSet<T>(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        ifLazy = vector<bool>(n4,0);
        arr = &v;
        end = n - 1;
        root = 1;
        build(0, end, 1);
        arr = nullptr;
    }

    void show(int p, int depth = 0) {
        if (p > n4 || tree[p] == 0) return;
        show(p * 2, depth + 1);
        for (int i = 0; i < depth; ++i) putchar('\t');
        printf("%d:%d\n", tree[p], lazy[p]);
        show(p * 2 + 1, depth + 1);
    }

    T range_sum(int l, int r) { return range_sum(l, r, 0, end, root); }

    void range_set(int l, int r, T val) { range_set(l, r, val, 0, end, root); }
};

} // namespace oi_wiki_seg