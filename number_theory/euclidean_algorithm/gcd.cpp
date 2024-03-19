#include<algorithm>
#include<cstdio>
using namespace std;

// 最大公約数
int gcd(int x,int y)
{
    return y?gcd(y,x%y):x;
}

// 最小公倍数(lca是什么？)
int lcm(int x,int y)
{
    int g=gcd(x,y);
    return x/g*y;
}

int main()
{
    return 0;
}