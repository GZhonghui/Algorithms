#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

class Wythoff
{
protected:
    int x,y;

public:
    Wythoff()=default;
    Wythoff(int x,int y):x(x),y(y){}

public:
    ~Wythoff()=default;

public:
    bool win()
    {
        //make sure x<y
        if(x>y) swap(x,y);

        int k=y-x;
        int res=k*(1.0+sqrt(5.0))/2.0;
        
        return res!=x;
    }
};

int main()
{
    return 0;
}