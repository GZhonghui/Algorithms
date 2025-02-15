/*

威佐夫博弈

问题描述：
有两堆石子，每次每个人有两种策略：1.在一堆中取任意个石子 2.在两堆中取相同数量的石子
每次取石子数量必须大于等于1，最后把所有石子全部取完的玩家获胜，判断是否为先手必胜状态

*/

#include <algorithm>
#include <cstdio>
#include <cmath>

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
    bool win() // 判断这是一个（先手）必胜状态吗
    {
        //make sure x<y
        if(x>y) std::swap(x,y);

        int k=y-x;
        int res=k*(1.0+sqrt(5.0))/2.0;
        
        return res!=x;
    }
};