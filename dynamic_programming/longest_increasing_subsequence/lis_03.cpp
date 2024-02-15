#include <algorithm>
#include <cstdio>

const int maxn=1e5+10;

int nums[maxn],buffer[maxn],n;

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i+=1) scanf("%d",nums+i);

    buffer[0]=1,buffer[1]=nums[0];

    for(int i=1;i<n;i+=1)
    {
        // 使用lower_bound还是upper_bound，区别在于是“严格上升”还是“不下降”
        int index = std::lower_bound(buffer+1,buffer+1+buffer[0],nums[i])-buffer-1;
        if(index>=buffer[0])
        {
            buffer[0]+=1;
            buffer[buffer[0]]=nums[i];
        }else
        {
            buffer[index+1]=nums[i];
        }
    }

    printf("%d\n",buffer[0]);

    return 0;
}