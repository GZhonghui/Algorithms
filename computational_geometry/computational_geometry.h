/*

计算几何的基础定义

*/

#ifndef COMPUTATIONAL_GEOMETRY_H
#define COMPUTATIONAL_GEOMETRY_H

#include <algorithm>
#include <cstdint>
#include <vector>
#include <cmath>

namespace computational_geometry
{

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1);

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

    T dot(const Vector2 &rhx) const
    {
        return x * rhx.x + y * rhx.y;
    }

    Vector2 hadamard(const Vector2 &rhx) const
    {
        return Vector2(x * rhx.x, y * rhx.y);
    }

    double len() const
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

    double dist(const Vector2 &rhx) const
    {
        return (*this - rhx).len();
    }
};

typedef Vector2<double> Point2f;
typedef Vector2<double> Direction2f;

// 线段
class Segment2f
{
public:
    Point2f p1, p2;

    Segment2f() : p1(0, 0), p2(1, 0) {}
    Segment2f(const Point2f &p1, const Point2f &p2) : p1(p1), p2(p2) {}

    // 线段上任意一点
    Point2f get_point(double t) const
    {
        return p1 + (p2 - p1) * t;
    }

    // 线段长度
    double len() const
    {
        return p1.dist(p2);
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
    Point2f get_point(double t) const
    {
        return p + d * t;
    }

    // -1 在射线左侧，0 在射线上，1 在射线右侧
    int8_t relatively(const Point2f &point)
    {
        Direction2f rhx_v = point - p;
        double result = rhx_v.x * d.y - d.x * rhx_v.y;
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
    double angle(const Line2f &rhx) const {
        // TODO: 检查一下AI给出的公式
        return atan2(rhx.p2.y - rhx.p1.y, rhx.p2.x - rhx.p1.x) - atan2(p2.y - p1.y, p2.x - p1.x);
    }
};

// 圆
class Circle2f
{
public:
    Point2f center;
    double r;

    Circle2f() : center(0, 0), r(1) {}
    Circle2f(const Point2f &center, double r) : center(center), r(r) {}
    // 从两个点构造一个最小圆
    Circle2f(const Point2f &p1, const Point2f &p2) {
        Segment2f seg(p1, p2);
        center = seg.get_point(0.5);
        r = seg.len() / 2;
    }
    // 从三个点构造一个最小圆
    Circle2f(const Point2f &p1, const Point2f &p2, const Point2f &p3) {
        // TODO
        // 可以参考正弦定理
    }

    // 圆的面积
    double area() const
    {
        return pi * r * r;
    }

    // 圆的周长
    double circumference() const
    {
        return 2 * pi * r;
    }

    bool inside(const Point2f &p) const
    {
        return center.dist(p) < r + eps;
    }
};

// 按角度排序
bool sort_by_angle(const Point2f &p1, const Point2f &p2) {
    return atan2(p1.y, p1.x) < atan2(p2.y, p2.x);
}

} // namespace computational_geometry

#endif