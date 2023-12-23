#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
struct Point
{
    int x,y;Point(int x,int y):x(x),y(y){}
    bool operator<(const Point &rhx)const
    {
        return this->x<rhx.x;
    }
};

vector<Point> points;
int N;
int main()
{
    freopen("in.txt","r",stdin);
    scanf("%d",&N);for(int i=1;i<=N;i+=1)
    {
        int x,y;scanf("%d %d",&x,&y);
        points.push_back(Point(x,y));
    }sort(points.begin(),points.end());

    return 0;
}