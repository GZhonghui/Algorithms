#include<cstdio>
#include<algorithm>
#include<deque>

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

sliding_window_min_max<float> solver;

int main()
{
    int n = 5;
    float data[5] = {3.14f, 2.88f, 5.0f, 10.0f, -5.0f};
    
    solver.init(3);
    for(int i=0;i<5;i+=1)
    {
        solver.add(data[i]);
        printf("%d: min = %f, max = %f\n",i,solver.min_in_last_window(),solver.max_in_last_window());
    }

    return 0;
}