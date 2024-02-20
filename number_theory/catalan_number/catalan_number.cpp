#include<iostream>
using namespace std;
long long Ans[25];int N;
int main()
{
    Ans[0] = 1;
    scanf("%d",&N);
    for(int i=1;i<=N;i+=1) Ans[i]=Ans[i-1]*(4*i-2)/(i+1);
    printf("%d\n",Ans[N]);
    return 0;
}
