#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;
struct Point
{
    int x,y;
    Point(int x,int y):x(x),y(y){}
    double ODis(const Point &rhx)const
    {
        int dx(x-rhx.x),dy(y-rhx.y);
        return sqrt(dx*dx+dy*dy);
    }
    int ManhattanDis(const Point &rhx)const
    {
        int dx(abs(x-rhx.x)),dy(y-rhx.y);
        return dx+dy;
    }
    int ChebyshevDis(const Point &rhx)const
    {
        int dx(abs(x-rhx.x)),dy(y-rhx.y);
        return max(dx,dy);
    }
    

};
struct Line
{
    Line(){}
};
int main()
{
    freopen("in.txt","r",stdin);

    return 0;
}