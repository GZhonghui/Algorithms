/*

滑动窗口 sliding_window
这是一种思维技巧

## 基础滑动窗口
维护l和r，分别前进

## 滑动窗口最值
问题描述：数字序列长度为N，则其中长度为K的区间有**N-K+1**个，问**每一个区间**的最值  
此类问题也可以使用**线段树**解决，但是滑动窗口的时间更优  
基本思路：  
考虑一下维护最小值的情况，一个滑动窗口，**i<j**，Ai先进入窗口，Ai也先退出窗口
如果**Aj<Ai**，那么Aj进入窗口后，Ai就永远没有机会成为区间最小值了  
通俗理解：你是二年级，有一个一年级的学弟比你rating高
那么你在毕业之前不可能成为全校第一了（所以你可以在队列中被提前pop了）  
数据使用双端队列维护

## 例题
- https://atcoder.jp/contests/typical90/tasks/typical90_ah 基础滑动窗口

*/

#include <iostream>
#include <algorithm>
#include <deque>
#include <cstdio>

namespace sliding_window {

// 将数字依次加入滑动窗口 到达边界后也自动删除 维护窗口内的min和max值
template<class T>
class sliding_window_min_max
{
protected:
    struct node
    {
        int id;
        T value;
    };

protected:
    int window_size = 1, now_index = 0;
    std::deque<node> min_q,max_q;

public:
    void init(int window_size)
    {
        this->window_size = window_size;
        now_index = 0;
        min_q.clear();
        max_q.clear();
    }

    void add(T new_number)
    {
        node new_node = (node){++now_index,new_number};

        if(min_q.size() && new_node.id - min_q.front().id >= window_size)
        {
            min_q.pop_front();
        }
        while(min_q.size() && min_q.back().value >= new_node.value)
        {
            min_q.pop_back();
        }
        min_q.push_back(new_node);

        if(max_q.size() && new_node.id - max_q.front().id >= window_size)
        {
            max_q.pop_front();
        }
        while(max_q.size() && max_q.back().value <= new_node.value)
        {
            max_q.pop_back();
        }
        max_q.push_back(new_node);
    }

    T min_in_last_window()
    {
        if(min_q.size())
        {
            return min_q.front().value;
        }
        return (T)0;
    }

    T max_in_last_window()
    {
        if(max_q.size())
        {
            return max_q.front().value;
        }
        return (T)0;
    }
};

void toolkit() {
    sliding_window_min_max<float> solver;

    int n = 5;
    float data[5] = {3.14f, 2.88f, 5.0f, 10.0f, -5.0f};
    
    solver.init(3);
    for(int i=0;i<5;i+=1)
    {
        solver.add(data[i]);
        printf(
            "%d: min = %f, max = %f\n",
            i,solver.min_in_last_window(),solver.max_in_last_window()
        );
    }
}

} // namespace sliding_window