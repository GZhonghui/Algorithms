#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn=1024;

int N,Data[maxn];

inline int Lowbit(int x)
{
    return x&(-x);
}

//求前x个元素的和
int sum(int* array,int x)
{
    int ans=0;
    for(int i=x;i>=1;i-=Lowbit(i)) ans+=array[i];
    return ans;
}

//更新第x个元素
void update(int* array,int x,int delta)
{
    for(int i=x;i<maxn;i+=Lowbit(i)) array[i]+=delta;
}

int main()
{
    int input;
    scanf("%d",&N);
    memset(Data,0,sizeof(Data));

    //建立树的时候，所有元素初始为0
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&input);
        update(Data,i,input);
    }

    for(int i=1;i<=N;i++)
    {
        printf("Sum of Sum%d: %d\n",i,sum(Data,i));
    }

    return 0;
}
