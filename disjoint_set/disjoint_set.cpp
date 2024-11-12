#include<algorithm>
#include<cstdio>
using namespace std;

namespace disjoint_set {

const int maxn=1024;

int fa[maxn];

int root(int x)
{
    //路径压缩
    return fa[x]==x?x:fa[x]=root(fa[x]);
}

inline bool Judge(int x,int y)
{
    //判断两个节点是否已经连接
    return root(x)==root(y);
}

inline void Link(int x,int y)
{
    int rx=root(x),ry=root(y);
    fa[rx]=ry;
}

inline void init()
{
    for(int i=0;i<maxn;i++) fa[i]=i;
}

} // namespace disjoint_set

int main()
{
    disjoint_set::init();

    return 0;
}
