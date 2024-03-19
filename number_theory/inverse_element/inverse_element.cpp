#include<algorithm>
#include<cstdio>

const int mod=1009; // 素数

// 扩展欧几里得法
typedef long long ll;
void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a, ll p){
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}
int inverse_element_exgcd(int x)
{

}

// 快速幂法
int inverse_element_qpow(int x)
{

}

int main()
{
    return 0;
}