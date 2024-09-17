#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=(1<<10)+100;
struct Lowbit_Adv
{
    int row,colum;
    long long C1[maxn][maxn],C2[maxn][maxn],C3[maxn][maxn],C4[maxn][maxn];
    int lowbit(int x){return x&(-x);}
    // 待验证：下标范围是[1,n] & [1,m]，下述的操作也都是闭区间
    void init(int n,int m)
    {
        this->row=n;this->colum=m;
        memset(C1,0,sizeof(C1));memset(C2,0,sizeof(C2));
        memset(C3,0,sizeof(C3));memset(C4,0,sizeof(C4));
    }
    void notuse_add(int x,int y,long long val) // 最好别用这个
    {
        for(int i=x;i<=row;i+=lowbit(i))
            for(int j=y;j<=colum;j+=lowbit(j))
            {
                C1[i][j]+=val,C2[i][j]+=val*x;
                C3[i][j]+=val*y,C4[i][j]+=val*x*y;
            }
    }
    void range_add(int x1,int y1,int x2,int y2,long long x) // 待验证：闭区间
    {
        notuse_add(x1,y1,x);notuse_add(x1,y2+1,-x);
        notuse_add(x2+1,y1,-x);notuse_add(x2+1,y2+1,x);
    }
    long long notuse_ask(int x,int y) // 最好别用这个
    {
        long long ret=0;
        for(int i=x;i>0;i-=lowbit(i))
            for(int j=y;j>0;j-=lowbit(j))
            {
                ret+=(x+1)*(y+1)*C1[i][j];ret+=C4[i][j];
                ret-=(y+1)*C2[i][j]+(x+1)*C3[i][j];
            }return ret;
    }
    // 待验证：x1 y1 能取到0吗？（还是要>=1？）
    long long range_ask(int x1,int y1,int x2,int y2) // 待验证：闭区间
    {
        return notuse_ask(x2,y2)-notuse_ask(x1-1,y2)-notuse_ask(x2,y1-1)+notuse_ask(x1-1,y1-1);
    }
}ac;

int main()
{
    return 0;
}