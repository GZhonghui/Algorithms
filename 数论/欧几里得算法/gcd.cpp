#include<algorithm>
#include<cstdio>
using namespace std;

int gcd(int x,int y)
{
    return y?gcd(y,x%y):x;
}

int lca(int x,int y)
{
    int g=gcd(x,y);
    return x/g*y;
}

int main()
{
    return 0;
}