/*

傅里叶变换(fourier_transform) 实现大数乘法
代码年久失修 仅供参考 推荐使用 ACL 的版本（卷积）
根据卷积定理，时域卷积等于频域乘积，可以用于快速计算大整数相乘

*/

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>

namespace FFT_quick_multiply {

using namespace std;
const int maxn=1e5+10;
const double pi=acos(-1.0);

class Complex
{
public:
    double re,im;
    Complex(double r=0,double i=0):re(r),im(i){}
    Complex operator+(const Complex &rhs)
    {
        return Complex(re+rhs.re,im+rhs.im);
    }
    Complex operator*(const Complex &rhs)
    {
        return Complex(re*rhs.re-im*rhs.im,re*rhs.im+im*rhs.re);
    }
    Complex operator-(const Complex &rhs)
    {
        return Complex(re-rhs.re,im-rhs.im);
    }
};

void change(Complex *y,int len)
{
    for(int i=1,j=len>>1;i+1<len;i++)
    {
        if(i<j) swap(y[i],y[j]);
        int k=len>>1;
        while(j>=k)
        {
            j-=k;
            k>>=1;
        }
        if(j<k) j+=k;
    }
}

void FFT(Complex *y,int len,int on=1)
{
    change(y,len);
    for(int i=2;i<=len;i<<=1)
    {
        Complex wn(cos(-on*2*pi/i),sin(-on*2*pi/i));
        for(int j=0;j<len;j+=i)
        {
            Complex w(1);
            int o=i>>1;
            for(int k=j;k<j+o;k++)
            {
                Complex u=y[k],t=w*y[k+o];
                y[k]=u+t;
                y[k+o]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    {
        for(int i=0;i<len;i++)
        {
            y[i].re/=len;
        }
    }
}

int ans[maxn<<2]{0};
Complex ComA[maxn<<2],ComB[maxn<<2];

void solve(const char *A,const char *B)
{
    int lenA=strlen(A),lenB=strlen(B);
    int len=1;while(len<lenA+lenB) len<<=1;

    for(int i=0;i<lenA;i+=1) ComA[i]=Complex(A[lenA-i-1]-'0',0);
    for(int i=lenA;i<len;i+=1) ComA[i]=Complex();
    for(int i=0;i<lenB;i+=1) ComB[i]=Complex(B[lenB-i-1]-'0',0);
    for(int i=lenB;i<len;i+=1) ComB[i]=Complex();

    FFT(ComA,len,1);FFT(ComB,len,1);
    for(int i=0;i<len;i+=1) ComA[i]=ComA[i]*ComB[i];
    FFT(ComA,len,-1);

    for(int i=0;i<len;i+=1) ans[i]=int(ComA[i].re+0.5);
    for(int i=0;i<len;i+=1)
    {
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }

    int endPoint=lenA+lenB-1;
    while(ans[endPoint]<=0&&endPoint>=1) endPoint-=1;
    for(int i=endPoint;i>=0;i-=1) putchar(ans[i]+'0');puts("");
}

void toolkit() {
    FFT_quick_multiply::solve("127312387", "823013017023"); // 104779751729269763901
}

} // namespace FFT_quick_multiply