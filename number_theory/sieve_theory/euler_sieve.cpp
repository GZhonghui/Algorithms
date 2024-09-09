#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1024;

struct Sieve
{
    bool check[maxn];
    vector<int> prime; // 找到的质数

    void init()
    {
        memset(check,0,sizeof(check));
        prime.clear();
    }
    void calc(int n) // 找到[,n]以内的质数
    {
        for(int i=2;i<=n;i++)
        {
            if(!check[i]) prime.push_back(i);
            for(int j=0;j<prime.size();j++)
            {
                if(i*prime[j]>n) break;
                check[i*prime[j]]=true;
                if(i%prime[j]==0) break;
            }
        }
    }
};
int main()
{
    return 0;
}
