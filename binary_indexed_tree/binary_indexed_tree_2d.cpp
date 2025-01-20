/*

注意：代码年代久远，正确性未实际验证过

二维树状数组，支持区间加减和区间查询

*/

#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn=(1<<10)+10;

class Lowbit2D
{
public:
    int row,colum;
    int C1[maxn][maxn],C2[maxn][maxn];
    int C3[maxn][maxn],C4[maxn][maxn];
public:
    // 下标范围是[1,n] & [1,m]，下述的操作也都是闭区间
    // x 属于 [1,n]，y 属于 [1,m]
    void init(int n,int m)
    {
        this->row=n;this->colum=m;
        memset(C1,0,sizeof(C1));memset(C2,0,sizeof(C2));
        memset(C3,0,sizeof(C3));memset(C4,0,sizeof(C4));
    }
    void range_add(int x1,int y1,int x2,int y2,int x)
    {
        add(x1,y1,x);
        add(x1,y2+1,-x);
        add(x2+1,y1,-x);
        add(x2+1,y2+1,x);
    }
    int range_ask(int x1,int y1,int x2,int y2)
    {
        return ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
    }
protected:
    int lowbit(int x){return x&(-x);}

    void add(int x,int y,int val)
    {
        for(int i=x;i<=row;i+=lowbit(i))
        for(int j=y;j<=colum;j+=lowbit(j))
        {
            C1[i][j]+=val;
            C2[i][j]+=val*x;
            C3[i][j]+=val*y;
            C4[i][j]+=val*x*y;
        }
    }
    int ask(int x,int y)
    {
        int ret=0;
        for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
        {
            ret+=(x+1)*(y+1)*C1[i][j]+C4[i][j];
            ret-=(y+1)*C2[i][j]+(x+1)*C3[i][j];
        }
        return ret;
    }
};