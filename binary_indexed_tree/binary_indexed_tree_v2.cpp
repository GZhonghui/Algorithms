#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1024;
struct LowBitTree
{
    int C[maxn],n;
    void init(int n=maxn-1) // 待验证：n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(int)*maxn);
    }
    int lowbit(int x){ return x&(-x); }
    int Sum(int pos) // 待验证：计算Sum[1,pos]
    {
        int ans=0;
        for(int i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(int pos,int value) // 待验证：在pos的位置增加value
    {
        for(int i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
};
int main()
{
    return 0;
}