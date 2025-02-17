/*

DisjointSet dsu
并查集 带路径压缩
维护n个元素之间的集合关系，可以快速：将两个元素所属的集合合并、判断两个元素是否属于同一个集合
例题推荐：AtCoder/Beginner_Contest_370/d.cpp

DisjointSetWithType
带权并查集

*/

#include <algorithm>
#include <iostream>

namespace disjoint_set {
using namespace std;

const int maxn = 5e4 + 8;

class DisjointSet {
protected:
    int fa[maxn];

public:
    // 初始化
    void init()
    {
        for (int i = 0; i < maxn; i++)
            fa[i] = i;
    }

    // 查找根节点
    int root(int x)
    {
        // 路径压缩 默认启用
        // 在少部分的题目中 可能不能使用路径压缩 毕竟路径压缩会破坏树的结构
        return fa[x] == x ? x : fa[x] = root(fa[x]);
    }

    // 判断两个节点是否已经连接
    bool judge(int x, int y)
    {
        return root(x) == root(y);
    }

    // 连接两个节点
    void link(int x, int y)
    {
        int rx = root(x), ry = root(y);
        fa[rx] = ry;
    }
};

// 带权并查集
class DisjointSetWithType {
protected:
    // relation: relation with father
    int fa[maxn], relation[maxn], type_cnt;

public:
    void init(int type_cnt) {
        this->type_cnt = type_cnt;
        for(int i = 0; i < maxn; i++) {
            fa[i] = i;
            relation[i] = 0;
        }
    }

    // root & relation with root
    pair<int, int> root(int x) {
        if(x == fa[x]) {
            return make_pair(x, 0);
        }
        auto res = root(fa[x]);
        // compress path
        fa[x] = res.first;
        relation[x] = (relation[x] + res.second) % type_cnt;
        return make_pair(res.first, relation[x]);
    }

    // x -> y, +delta
    bool link(int x, int y, int delta) {
        auto rx = root(x), ry = root(y);
        if(rx.first == ry.first) {
            // same root, may have conflict
            return delta % type_cnt == (type_cnt - rx.second + ry.second) % type_cnt;
        } else {
            // different root, no conflict
            fa[ry.first] = x;
            relation[ry.first] = (type_cnt + delta - ry.second) % type_cnt;
        }
        return true;
    }
};

// 本函数代码是经典例题「POJ 1182 食物链」（http://poj.org/problem?id=1182）的代码
void toolkit() {
    DisjointSetWithType ds;
    ds.init(3);

    int n, k, t, x, y, res = 0;
    cin >> n >> k;
    while(k--) {
        cin >> t >> x >> y;
        if (x > n || y > n || x < 1 || y < 1) {
            res += 1;
        } else if(t == 1) {
            res += ds.link(x, y, 0) ? 0 : 1;
        } else if(t == 2) {
            res += ds.link(x, y, 1) ? 0 : 1;
        }
    }
    cout << res << endl;
}

} // namespace disjoint_set