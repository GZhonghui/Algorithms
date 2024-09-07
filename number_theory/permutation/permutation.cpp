#include<algorithm>
#include<iostream>
#include<cstdint>
#include<vector>

int main()
{
    int64_t k;
    std::vector<int64_t> index;

    std::cin >> k;

    index.push_back(0);
    for(int64_t i=1;i<=k;i+=1)
    {
        index.push_back(i);
    }
    // 注意index是不是从有序的状态开始的

    for(uint32_t i=0;i<((uint32_t)1 << k);i+=1)
    {
        do{
            // calc by i & index
            // i和index是两种不同的枚举方式

        }while(std::next_permutation(index.begin()+1,index.end()));
    }

    return 0;
}

