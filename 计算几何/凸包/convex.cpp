//有点丑orz
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<unordered_set>
#include<vector>
#include<stack>
#include<ctime>
#define RANDOM
using namespace std;
const double eps=1e-6;
struct Vector2
{
    double x,y;
    Vector2()=default;
    Vector2(double k):x(k),y(k){}
    Vector2(double x,double y):x(x),y(y){}
    Vector2 operator+(const Vector2 &rhx) const
    {
        return Vector2(x+rhx.x,y+rhx.y);
    }
    Vector2 operator-(const Vector2 &rhx) const
    {
        return Vector2(x-rhx.x,y-rhx.y);
    }
    double distance(const Vector2 &rhx) const
    {
        double dx=x-rhx.x,dy=y-rhx.y;
        return std::sqrt(dx*dx+dy*dy);
    }
    double normal() const
    {
        return std::sqrt(x*x+y*y);
    }
    Vector2 normalized() const
    {
        double len=normal();
        return Vector2(x/len,y/len);
    }
};
typedef Vector2 Point;
typedef Vector2 Direction;
int relatively(const Point &origin,const Direction &forward,const Point &point)
{
    Direction rhx_v=point-origin;
    double result=rhx_v.x*forward.y-forward.x*rhx_v.y;
    if(std::abs(result)<eps) return 0;
    return result<0?-1:1;
}
bool andrew_sort(const Point &A,const Point &B)
{
    if(A.x==B.x)
    {
        return A.y<B.y;
    }
    return A.x<B.x;
}
unordered_set<int> used;
vector<Point> points;
stack<Point> order;
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
        points.push_back(Point(x,y));
    }
    sort(points.begin(),points.end(),andrew_sort);
    order.push(points[0]);
    for(int i=2,_size=points.size();i<=_size;i=i+1)
    {
        const Point &now=points[i-1];
        while((int)order.size()>=2)
        {
            Point point=order.top();
            order.pop();
            Point origin=order.top();
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
    Point top=order.top();
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
        const Point &now=points[i-1];
        if(used.count(i)) continue;
        while((int)order.size()>=2)
        {
            Point point=order.top();
            order.pop();
            Point origin=order.top();
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
int main()
{
    return solve();
}