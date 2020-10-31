#include<algorithm>
#include<cstdio>
#include<vector>
#include<cmath>

const double eps=1e-8;

class Vector2f
{
public:
    double x,y;
public:
    Vector2f(double x=0,double y=0):x(x),y(y){}
    ~Vector2f()=default;
public:
    double distance(const Vector2f &rhx) const
    {
        double dx=x-rhx.x;
        double dy=y-rhx.y;

        return std::sqrt(dx*dx+dy*dy);
    }
    Vector2f mid(const Vector2f &rhx) const
    {
        return Vector2f((x+rhx.x)/2,(y+rhx.y)/2);
    }
    void rotate(double angle)
    {
        //Code here
    }
};

typedef Vector2f Point;
typedef Vector2f Direction;

class Circle
{
public:
    Point center;
    double r;
public:
    Circle()=default;
    Circle(const Point &center,double r):center(center),r(r){}
    Circle(const Point &x,const Point &y)
    {
        center=x.mid(y);
        r=x.distance(y)/2;
    }
    Circle(const Point &x,const Point &y,const Point &z)
    {
        //Code here
    }
    ~Circle()=default;
public:
    bool inside(const Point &test_point) const
    {
        return center.distance(test_point)<r+eps;
    }
    void print() const
    {
        printf("[Circle]:(%lf,%lf),r=%lf.",center.x,center.y,r);
    }
};

class MinCircle
{
protected:
    std::vector<Point> points;
public:
    MinCircle()=default;
    ~MinCircle()=default;
protected:
    bool find_out(int l,int r,const Circle &circle,Point &out_point)
    {
        for(int i=l;i<=r;i+=1)
        {
            if(!circle.inside(points[i-1]))
            {
                out_point=points[i-1];
                return true;
            }
        }

        return false;
    }
public:
    void add_point(const Point &point)
    {
        points.push_back(point);
    }
    void destroy()
    {
        points.clear();
    }
public:
    void min_circle(Circle &result)
    {
        double r=0;
        int n=points.size();

        if(!n) return;

        if(n==1)
        {
            result.center=points[0];
            result.r=eps;

            return;
        }

        result=Circle(points[0],points[1]);

        for(int i=3;i<=n;i+=1)
        {
            const Point &now=points[i-1];

            if(!result.inside(now))
            {
                //now[Point] is on the new circles side
                result=Circle(points[0],now);

                Point next_x;
                if(find_out(2,i-1,result,next_x))
                {
                    result=Circle(now,next_x);

                    Point next_y;
                    if(find_out(1,i-1,result,next_y))
                    {
                        //Find 3 outside points
                        result=Circle(now,next_x,next_y);
                    }
                }
            }
        }
    }
};

int main()
{
    MinCircle *solver=new MinCircle;

    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i+=1)
    {
        double x,y;
        scanf("%lf %lf",&x,&y);
        solver->add_point(Point(x,y));
    }

    Circle result;
    solver->min_circle(result);
    result.print();

    delete solver;
    return 0;
}