/*

treap 是一种二叉搜索树
借用了堆的灵感
每个节点有一个随机权值，使得树的期望高度为 O(logn)
比较容易实现的一种平衡树，但是速度并不是最快的
好用又好写

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cassert>
#include <ctime>

namespace treap {

    using namespace std;

    struct treap_node {
        treap_node *left,*right;
        int value,cnt,siz;
        uint64_t pro;

        treap_node(treap_node *l,treap_node *r,int v,uint64_t p)
        {
            left=l,right=r,value=v,pro=p;
            cnt=siz=1;
        }
    };

    class treap {
    protected:
        treap_node *root;

        //随机得到一个优先级
        uint64_t get_pro()
        {
            return (uint64_t)rand();
        }

        void re_cal(treap_node *now)
        {
            now->siz=now->cnt;
            if(now->left) now->siz+=now->left->siz;
            if(now->right) now->siz+=now->right->siz;
        }

        void clear_tree(treap_node *now)
        {
            if(!now) return;
            if(now->left) clear_tree(now->left);
            if(now->right) clear_tree(now->right);
            delete now;
        }

    protected:
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

        treap_node *exist(treap_node *now,int value)
        {
            if(!now) return nullptr;
            if(value==now->value) return now;
            if(value<now->value) return exist(now->left,value);
            return exist(now->right,value);
        }

        int get_rank(treap_node *now,int value)
        {
            if(!now) return -1; int left_size=(now->left?now->left->siz:0);
            if(value<now->value) return now->left?get_rank(now->left,value):-1;
            if(value==now->value) return left_size+1;
            if(!now->right) return -1; return left_size+(now->cnt)+get_rank(now->right,value);
        }

        int get_kth_element(treap_node *now,int kth)
        {
            if(now->left) {
                if(now->left->siz>=kth) return get_kth_element(now->left,kth);
                else kth-=now->left->siz;
            }
            if(kth<=now->cnt) return now->value;
            if(now->right&&kth-now->cnt<=now->right->siz)
                return get_kth_element(now->right,kth-now->cnt);
            return -1;
        }

    public:
        treap() {
            root=nullptr;
        }

        ~treap() {
            clear_tree(root);
        }

        void insert(int value) {
            root = insert(root,value);
        }

        void del(int value) {
            root = del(root,value);
        }

        bool exist(int value) {
            return exist(root,value)!=nullptr;
        }

        int get_rank(int value) { //[1, n]
            return get_rank(root,value);
        }

        int get_count(int value) {
            treap_node *node=exist(root,value);
            return node?node->cnt:0;
        }

        int get_kth_element(int kth) { // [1, n]
            return get_kth_element(root,kth);
        }

        int size() {
            return root?root->siz:0;
        }
    };

    inline void treap_toolkit() {
        srand(time(nullptr));

        treap t;

        int n = 10;
        cout << "insert: ";
        for(int i = 0; i < n; ++i) {
            int x = rand() % 20 + 10;
            cout << x << " ";
            t.insert(x);
        }
        cout << endl;

        assert(t.size() == n);
        cout << "sorted: ";
        for(int i = 1; i <= n; ++i) {
            int x = t.get_kth_element(i);
            cout << x << " ";

            assert(t.exist(x));
            assert(t.get_rank(x) <= i);

            for(int _t = 1, _cnt = t.get_count(x); _t < _cnt; ++_t) {
                cout << "** ";
                i += 1;
            }
        }
        cout << endl;

    }
} // namespace treap