/*

并查集 带路径压缩
维护n个元素之间的集合关系，可以快速：将两个元素所属的集合合并、判断两个元素是否属于同一个集合
例题推荐：AtCoder/Beginner_Contest_370/d.cpp

*/

#include <algorithm>
#include <cstdio>
using namespace std;

namespace disjoint_set {

const int maxn = 1024;

int fa[maxn];

// 初始化
inline void init()
{
    for (int i = 0; i < maxn; i++)
        fa[i] = i;
}

// 查找根节点
int root(int x)
{
    // 路径压缩
    return fa[x] == x ? x : fa[x] = root(fa[x]);
}

inline bool Judge(int x,int y)
{
    //判断两个节点是否已经连接
    return root(x) == root(y);
}

inline void Link(int x,int y)
{
    int rx = root(x), ry = root(y);
    fa[rx] = ry;
}

} // namespace disjoint_set
