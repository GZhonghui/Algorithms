// 代码来源：https://www.cnblogs.com/tttkf/p/15895646.html

#include<bits/stdc++.h>
using namespace std;

int f[200 + 5];
map<int, bool> mp;

int main()
{
    f[1] = f[2] = 1;
    for(int i = 3; i <= 50; i++) {
        f[i] = f[i - 1] + f[i - 2];
        mp[f[i]] = true;
    }
    int x;
    while(scanf("%d", &x) != EOF && x)
        printf("%s\n", mp[x] ? "Second win" : "First win");
    return 0;
}