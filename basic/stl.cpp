// C++ STL 演示各种用法
// C++ 14
// g++ stl.cpp -c --std=c++14

#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

template<typename T>
void stack_demo()
{
    stack<T> s;

    s.push((T)0); // 进栈
    T _t = s.top(); // 返回栈顶元素
    s.pop(); // 弹出栈顶元素
    bool _b = s.empty(); // 判断栈是否为空
    size_t _s = s.size(); // 栈内元素
    
    // s.swap();
    // s.emplace();
    // s.c;
}

template<typename T>
void queue_demo()
{
    // 普通队列
    queue<T> q;

    // 优先队列
    priority_queue<T> pq;

    // 双端队列
    // 循环队列
}

template<typename T>
void list_demo()
{
    list<T> l;

    l.insert((T)0); // 插入
    l.erase((T)0); // 擦除

    // 循环列表
}

template<typename T1, typename T2>
void pair_demo()
{
    pair<T1,T2> p = make_pair((T1)0,(T2)0);

    T1 _t1 = p.first; // 引用，不是指针
    T2 _t2 = p.second;

    p.swap(); // 干啥的
}

template<typename T>
void set_demo()
{
    set<T> s; // 集合
    multiset<T> ms; // 多重集合
    unordered_set<T> us; // 无序集合
    unordered_multiset<T> ums; // 无序多重集合
}

template<typename T>
void map_demo()
{

}