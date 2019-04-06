#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1024;
int fa[maxn];
int root(int x)
{
    //路径压缩
    return fa[x]==x?x:fa[x]=root(fa[x]);
}
bool Judge(int x,int y)
{
    //判断两个节点是否已经连接
    return root(x)==root(y);
}
void Link(int x,int y)
{
    int rx=root(x),ry=root(y);
    //if(rx!=ry)不需要判断
    fa[rx]=ry; 
}
void init()
{
    for(int i=0;i<maxn;i++) fa[i]=i;
}
int main()
{
    init();
    //Code
    return 0;
}
