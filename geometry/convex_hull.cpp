/*

convex_hull 凸包
有点丑orz

*/

#include "computational_geometry.h"
#include <unordered_set>
#include <stack>
#define RANDOM

namespace convex_hull {
using namespace std;
using namespace computational_geometry;

int relatively(const Point2f &origin,const Direction2f &forward,const Point2f &point)
{
    Direction2f rhx_v=point-origin;
    double result=rhx_v.x*forward.y-forward.x*rhx_v.y;
    if(std::abs(result)<eps) return 0;
    return result<0?-1:1;
}
bool andrew_sort(const Point2f &A,const Point2f &B)
{
    if(A.x==B.x)
    {
        return A.y<B.y;
    }
    return A.x<B.x;
}
unordered_set<int> used;
vector<Point2f> points;
stack<Point2f> order;

int solve()
{
    srand((unsigned)time(nullptr));
    int n;
#ifdef RANDOM
    n=rand()%66+3;
#else
    scanf("%d",&n);
#endif
    for(int i=1;i<=n;i+=1)
    {
        double x,y;
#ifdef RANDOM
        x=rand()%20+(rand()%1000)/(1000-1);
        y=rand()%20+(rand()%1000)/(1000-1);
        printf("%lf %lf\n",x,y);
#else
        scanf("%lf %lf",&x,&y);
#endif
        points.push_back(Point2f(x,y));
    }
    sort(points.begin(),points.end(),andrew_sort);
    order.push(points[0]);
    for(int i=2,_size=points.size();i<=_size;i=i+1)
    {
        const Point2f &now=points[i-1];
        while((int)order.size()>=2)
        {
            Point2f point=order.top();
            order.pop();
            Point2f origin=order.top();
            if(relatively(origin,now-origin,point)<=0)
            {
                used.erase(i-1);
                continue;
            }
            else
            {
                order.push(point);
                break;
            }
        }
        order.push(now);
        used.insert(i);
    }
    Point2f top=order.top();
    order.pop();
    while(!order.empty())
    {
        printf("Segment %lf %lf %lf %lf\n",order.top().x,order.top().y,top.x,top.y);
        top=order.top();
        order.pop();
    }
    order.push(points[(int)points.size()-1]);
    for(int i=(int)points.size()-1;i>=1;i-=1)
    {
        const Point2f &now=points[i-1];
        if(used.count(i)) continue;
        while((int)order.size()>=2)
        {
            Point2f point=order.top();
            order.pop();
            Point2f origin=order.top();
            if(relatively(origin,now-origin,point)<=0)
            {
                used.erase(i-1);
                continue;
            }
            else
            {
                order.push(point);
                break;
            }
        }
        order.push(now);
        used.insert(i);
    }
    top=order.top();
    order.pop();
    while(!order.empty())
    {
        printf("Segment %lf %lf %lf %lf\n",order.top().x,order.top().y,top.x,top.y);
        top=order.top();
        order.pop();
    }
    return 0;
}

} // namespace convex_hull