#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=1024;
struct Sieve
{
    bool check[maxn];
    vector<int> prime;
    void init()
    {
        memset(check,0,sizeof(check));
        prime.clear();
    }
    void calc(int n)
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
