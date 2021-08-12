#include<algorithm>
#include<cstdio>
#include<vector>
#include<ctime>
using namespace std;

const int maxn=1e5+10;
int values[maxn];

struct treap_node
{
    treap_node *left,*right;
    int value,cnt,siz;unsigned long long pro;
    treap_node(treap_node *l,treap_node *r,int v,unsigned long long p)
    {
        left=l,right=r,value=v,pro=p;cnt=siz=1;
    }
};

treap_node *Treap;
int totle_nodes;

//随机得到一个优先级
unsigned long long get_pro()
{
    return (unsigned long long)rand();
}

void re_cal(treap_node *now)
{
    now->siz=now->cnt;
    if(now->left) now->siz+=now->left->siz;
    if(now->right) now->siz+=now->right->siz;
}

treap_node* insert(treap_node *now,int value)
{
    if(!now)
        return new treap_node(nullptr,nullptr,value,get_pro());
    if(value==now->value) return now+0*(now->siz++,now->cnt++);
    if(value<(now->value))
    {
        now->left=insert(now->left,value);
        if(now->left->pro<now->pro)
        {
            treap_node *final_node=now->left;
            now->left=now->left->right;re_cal(now);
            final_node->right=now;re_cal(final_node);
            return final_node;
        }
        re_cal(now);return now;
    }
    now->right=insert(now->right,value);
    if(now->right->pro<now->pro)
    {
        treap_node *final_node=now->right;
        now->right=now->right->left;re_cal(now);
        final_node->left=now;re_cal(final_node);
        return final_node;
    }
    re_cal(now);return now;
}

treap_node* del(treap_node *now,int value)
{
    if(!now) return nullptr;
    if(value==now->value)
    {
        if(now->cnt>1) return now+0*(now->cnt--,now->siz--);
        int type=(now->left?1:0)+(now->right?1:0);
        treap_node *final_node;
        switch(type)
        {
            case 0:
                delete now;
                return nullptr;
            case 1:
                final_node=(now->left)?now->left:now->right;
                delete now;
                return final_node;
            case 2:
                if(now->left->pro<now->right->pro)
                {
                    final_node=now->left;
                    now->left=now->left->right;re_cal(now);
                    final_node->right=now;re_cal(final_node);
                    final_node->right=del(final_node->right,value);
                    re_cal(final_node);return final_node;
                }else
                {
                    final_node=now->right;
                    now->right=now->right->left;re_cal(now);
                    final_node->left=now;re_cal(final_node);
                    final_node->left=del(final_node->left,value);
                    re_cal(final_node);return final_node;
                }
        }
    }
    if(value<now->value) now->left=del(now->left,value);
    else now->right=del(now->right,value);
    re_cal(now);return now;
}

bool check(treap_node *now,int value)
{
    if(!now) return false;
    if(value==now->value) return true;
    if(value<now->value) return check(now->left,value);
    return check(now->right,value);
}

void clear_tree(treap_node *now)
{
    if(!now) return;
    if(now->left) clear_tree(now->left);
    if(now->right) clear_tree(now->right);
    delete now;
}

int get_rank(treap_node *now,int value)
{
    if(!now) return -1; int left_size=(now->left?now->left->siz:0);
    if(value<now->value) return now->left?get_rank(now->left,value):-1;
    if(value==now->value) return left_size+1;
    if(!now->right) return -1; return left_size+(now->cnt)+get_rank(now->right,value);
}

int get_ele(treap_node *now,int kth)
{
    if(now->left)
        if(now->left->siz>=kth) return get_ele(now->left,kth);
        else kth-=now->left->siz;
    if(kth<=now->cnt) return now->value;
    if(now->right&&kth-now->cnt<=now->right->siz)
        return get_ele(now->right,kth-now->cnt);return -1;
}

void init_all()
{
    clear_tree(Treap);
    Treap=nullptr;
    totle_nodes=0;
}

int main()
{
    return 0;
}