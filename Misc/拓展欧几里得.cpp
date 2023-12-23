#include<iostream>
#include<algorithm>
#include<cstdio>
long long exgcd(long long a,long long b,long long &x, long long &y)
{
  if(b==0)
  {
      x=1;
      y=0;
      return a;
  }
    long long r=exgcd(b,a%b,x,y);
    long long t=x;
    x=y;
    y=t-a/b*y;
    return r;
}
int main()
{
    return 0;
}