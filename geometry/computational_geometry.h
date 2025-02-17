/*

计算几何的基础定义 computational_geometry

基础习题
https://vjudge.net/contest/403271#problem/E
https://acm.hdu.edu.cn/showproblem.php?pid=1174 爆头

代码都是年久失修 使用之前注意检查

*/

#ifndef COMPUTATIONAL_GEOMETRY_H
#define COMPUTATIONAL_GEOMETRY_H

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>

namespace computational_geometry
{

using namespace std;
using i64 = int64_t;
using f64 = double;

const f64 eps = 1e-8;
const f64 pi = acos(-1);

template <typename T>
class Vector2
{
public:
    T x, y;

    Vector2() : x(0), y(0) {}
    Vector2(T k) : x(k), y(k) {}
    Vector2(T x, T y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &rhx) const
    {
        return Vector2(x + rhx.x, y + rhx.y);
    }

    Vector2 operator-(const Vector2 &rhx) const
    {
        return Vector2(x - rhx.x, y - rhx.y);
    }

    Vector2 operator*(T k) const
    {
        return Vector2(x * k, y * k);
    }

    T operator[](uint32_t k) const
    {
        switch(k)
        {
            case 0: return x;
            case 1: return y;
        }
        return 0;
    }

    T dot(const Vector2 &rhx) const
    {
        return x * rhx.x + y * rhx.y;
    }

    Vector2 hadamard(const Vector2 &rhx) const
    {
        return Vector2(x * rhx.x, y * rhx.y);
    }

    f64 len() const
    {
        return sqrt(x * x + y * y);
    }

    Vector2 normalize() const
    {
        T l = len();
        if (l < eps) {
            return Vector2(1, 0);
        }
        return Vector2(x / l, y / l);
    }

    f64 distance(const Vector2 &rhx) const
    {
        return (*this - rhx).len();
    }

    Vector2 mid(const Vector2 &rhx) const
    {
        return Vector2((x + rhx.x) / 2, (y + rhx.y) / 2);
    }
};

template <typename T>
class Vector3
{
public:
    T x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(T k) : x(k), y(k), z(k) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    ~Vector3() = default;

    Vector3 operator+(const Vector3 &rhx) const
    {
        return Vector3(x + rhx.x, y + rhx.y, z + rhx.z);
    }

    Vector3 operator-(const Vector3 &rhx) const
    {
        return Vector3(x - rhx.x, y - rhx.y, z - rhx.z);
    }

    Vector3 operator*(T k) const
    {
        return Vector3(x * k, y * k, z * k);
    }

    Vector3 operator/(T k) const
    {
        return Vector3(x / k, y / k, z / k);
    }

    T operator[](uint32_t k) const
    {
        switch(k)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        return 0;
    }

    bool operator<(const Vector3 &rhx) const
    {
        for(uint32_t i = 0; i < 3; i++)
        {
            if(operator[](i) > rhx[i])
            {
                return false;
            }
        }
        return true;
    }

    Vector3 hadamard_product(const Vector3 &rhx) const
    {
        return Vector3(x * rhx.x, y * rhx.y, z * rhx.z);
    }

    Vector3 cross_product(const Vector3 &rhx) const
    {
        return Vector3(y * rhx.z - rhx.y * z, rhx.x * z - x * rhx.z, x * rhx.y - rhx.x * y);
    }

    T dot_product(const Vector3 &rhx) const
    {
        return x * rhx.x + y * rhx.y + z * rhx.z;
    }

    Vector3 opposite() const
    {
        return Vector3(-x, -y, -z);
    }

    f64 normal() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalized() const
    {
        return operator/(normal());
    }

    f64 distance(const Vector3 &rhx) const
    {
        return operator-(rhx).normal();
    }

    Vector3 middle(const Vector3 &rhx) const // ？
    {
        return operator+(rhx).normalized();
    }

    void normalize()
    {
        (*this)=normalized();
    }

    void limit(f64 l,f64 r)
    {
        if(l>r) return;
        
        x=max(l,min(r,x));
        y=max(l,min(r,y));
        z=max(l,min(r,z));
    }
};

typedef Vector2<f64> Point2f;
typedef Vector2<f64> Direction2f;

typedef Vector3<f64> Point3f;
typedef Vector3<f64> Direction3f;

// 线段
class Segment2f
{
public:
    Point2f p1, p2;

    Segment2f() : p1(0, 0), p2(1, 0) {}
    Segment2f(const Point2f &p1, const Point2f &p2) : p1(p1), p2(p2) {}

    // 线段上任意一点
    Point2f get_point(f64 t) const
    {
        return p1 + (p2 - p1) * t;
    }

    // 线段长度
    f64 len() const
    {
        return p1.distance(p2);
    }
};

// 射线
class Ray2f
{
public:
    Point2f p;
    Direction2f d;

    Ray2f() : p(0, 0), d(1, 0) {}
    Ray2f(const Point2f &p, const Direction2f &d) : p(p), d(d.normalize()) {}

    // 射线上任意一点
    Point2f get_point(f64 t) const
    {
        return p + d * t;
    }

    // -1 在射线左侧，0 在射线上，1 在射线右侧
    int8_t relatively(const Point2f &point)
    {
        Direction2f rhx_v = point - p;
        f64 result = rhx_v.x * d.y - d.x * rhx_v.y;
        if(abs(result) < eps) return 0;
        return result <0 ? -1 : 1;
    }
};

// 直线
class Line2f
{
public:
    Point2f p1, p2; // p1 -> p2

    Line2f() : p1(0, 0), p2(1, 0) {}
    Line2f(const Point2f &p1, const Point2f &p2) : p1(p1), p2(p2) {}

    // 判断直线是否相交 如果相交则计算交点
    bool intersect(const Line2f &rhx, Point2f &res) const
    {
        Direction2f d1 = p2 - p1;
        Direction2f d2 = rhx.p2 - rhx.p1;
        if((d1.x * d2.y - d1.y * d2.x) < eps) {
            return false;
        }
        // TODO: 计算交点
        return true;
    }

    // 如果两条直线非平行 则求两条直线夹角
    // TODO: 检查是否平行
    f64 angle(const Line2f &rhx) const {
        // TODO: 检查一下AI给出的公式
        return atan2(rhx.p2.y - rhx.p1.y, rhx.p2.x - rhx.p1.x) - atan2(p2.y - p1.y, p2.x - p1.x);
    }
};

// 圆
class Circle
{
public:
    Point2f center;
    f64 r;

    Circle() : center(0, 0), r(1) {}
    Circle(const Point2f &center, f64 r) : center(center), r(r) {}
    // 从两个点构造一个最小圆
    Circle(const Point2f &p1, const Point2f &p2) {
        Segment2f seg(p1, p2);
        center = seg.get_point(0.5);
        r = seg.len() / 2;
    }
    // 从三个点构造一个最小圆
    Circle(const Point2f &p1, const Point2f &p2, const Point2f &p3) {
        // TODO
        // 可以参考正弦定理
    }

    // 圆的面积
    f64 area() const
    {
        return pi * r * r;
    }

    // 圆的周长
    f64 circumference() const
    {
        return 2 * pi * r;
    }

    bool inside(const Point2f &p) const
    {
        return center.distance(p) < r + eps;
    }

    void print() const
    {
        cout << "[Circle]: (" << center.x << ", " << center.y << "), r = " << r << "." << endl;
    }
};

// 按角度排序
bool sort_by_angle(const Point2f &p1, const Point2f &p2) {
    return atan2(p1.y, p1.x) < atan2(p2.y, p2.x);
}

} // namespace computational_geometry

#endif