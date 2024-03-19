// https://vjudge.net/contest/403271#problem/E
// https://acm.hdu.edu.cn/showproblem.php?pid=1174 爆头

#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;

const double eps=1e-8;

class Vector3f
{
public:
    double x,y,z;
public:
    Vector3f():x(0),y(0),z(0){}
    Vector3f(double k):x(k),y(k),z(k){}
    Vector3f(double x,double y,double z):x(x),y(y),z(z){}
    ~Vector3f()=default;
public:
    Vector3f operator+(const Vector3f &rhx) const
    {
        return Vector3f(x+rhx.x,y+rhx.y,z+rhx.z);
    }
    Vector3f operator-(const Vector3f &rhx) const
    {
        return Vector3f(x-rhx.x,y-rhx.y,z-rhx.z);
    }
    Vector3f operator*(double k) const
    {
        return Vector3f(x*k,y*k,z*k);
    }
    Vector3f operator/(double k) const
    {
        return Vector3f(x/k,y/k,z/k);
    }
    double operator[](unsigned int k) const
    {
        switch(k)
        {
            case 1:return x;
            case 2:return y;
            case 3:return z;
        }
        return 0;
    }
    bool operator<(const Vector3f &rhx) const
    {
        for(unsigned int i=1;i<=3;i+=1)
        {
            if(operator[](i)>rhx[i])
            {
                return false;
            }
        }
        return true;
    }
public:
    Vector3f hadamard_product(const Vector3f &rhx) const
    {
        return Vector3f(x*rhx.x,y*rhx.y,z*rhx.z);
    }
    Vector3f cross_product(const Vector3f &rhx) const
    {
        return Vector3f(y*rhx.z-rhx.y*z,rhx.x*z-x*rhx.z,x*rhx.y-rhx.x*y);
    }
    double dot_product(const Vector3f &rhx) const
    {
        return x*rhx.x+y*rhx.y+z*rhx.z;
    }
public:
    Vector3f opposite() const
    {
        return Vector3f(-x,-y,-z);
    }
    double normal() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    Vector3f normalized() const
    {
        return operator/(normal());
    }
    double distance(const Vector3f &rhx) const
    {
        return operator-(rhx).normal();
    }
    Vector3f middle(const Vector3f &rhx) const
    {
        return operator+(rhx).normalized();
    }
public:
    void normalize()
    {
        (*this)=normalized();
    }
    void limit(double l,double r)
    {
        if(l>r) return;
        
        x=max(l,min(r,x));
        y=max(l,min(r,y));
        z=max(l,min(r,z));
    }
};

typedef Vector3f Color;
typedef Vector3f Point;
typedef Vector3f Direction;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        double h1,r1,x,y,z;
        scanf("%lf %lf %lf %lf %lf",&h1,&r1,&x,&y,&z);

        Point target(x,y,z+h1-r1);

        double h2,r2,dx,dy,dz;
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&h2,&r2,&x,&y,&z,&dx,&dy,&dz);

        Point origin(x,y,z+0.9*h2-r2);
        Direction dir(dx,dy,dz);
        dir.normalize();

        Direction to_target=target-origin;

        double to_target_d=to_target.normal();

        double ssin=dir.cross_product(to_target).normal()/to_target_d;

        if(to_target_d*ssin+eps<r1) puts("YES");
        else puts("NO");
    }

    return 0;
}