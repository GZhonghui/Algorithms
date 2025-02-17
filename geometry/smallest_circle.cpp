/*

smallest_circle_problem 最小圆覆盖问题
给定n个坐标点，求一个半径最小的圆，使得所有的点都在圆内部

*/

#include "computational_geometry.h"

namespace smallest_circle {
using namespace computational_geometry;

class MinCircle
{
protected:
    std::vector<Point2f> points;

public:
    MinCircle()=default;
    ~MinCircle()=default;

protected:
    bool find_out(int l, int r, const Circle &circle, Point2f &out_point)
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
    void add_point(const Point2f &point)
    {
        points.push_back(point);
    }

    void destroy()
    {
        points.clear();
    }

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
            const Point2f &now=points[i-1];

            if(!result.inside(now))
            {
                //now[Point] is on the new circles side
                result=Circle(points[0],now);

                Point2f next_x;
                if(find_out(2,i-1,result,next_x))
                {
                    result=Circle(now,next_x);

                    Point2f next_y;
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

void toolkit()
{
    MinCircle *solver=new MinCircle;

    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i+=1)
    {
        double x,y;
        scanf("%lf %lf",&x,&y);
        solver->add_point(Point2f(x,y));
    }

    Circle result;
    solver->min_circle(result);
    result.print();

    delete solver;
}

} // namespace smallest_circle