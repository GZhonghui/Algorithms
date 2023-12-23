#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<ctime>
using namespace std;
struct Node
{
    int value,cnt;
    Node *left,*right,*father;
    Node(int x,Node *father=nullptr)
    {
        this->value=x;
        this->father=father;
        left=right=nullptr;
        cnt=1;
    }
};
static Node *SPlay=nullptr;
static Node *last_visit=nullptr;
void Single(Node *now)
{
    Node *parent=now->father;
    if(!parent) return ;
    Node *grand_parent=parent->father;
    if(now==parent->left)
    {
        parent->left=now->right;
        if(now->right) now->right->father=parent;
        now->right=parent;
        parent->father=now;
    }else if(now==parent->right)
    {
        parent->right=now->left;
        if(now->left) now->left->father=parent;
        now->left=parent;
        parent->father=now;
    }
    now->father=grand_parent;
    if(grand_parent)
        if(grand_parent->left==parent) grand_parent->left=now;
        else if(grand_parent->right==parent) grand_parent->right=now;
}
void LetsGo(Node* &Root,Node *now)
{
    if(!now) return;
    while(now->father)
    {
        Node *father=now->father;
        Node *grand=father->father;
        if(grand)
        {
            bool levelA=(father==grand->left);
            bool levelB=(now==father->left);
            if(levelA==levelB)//Like One
            {
                Single(now->father);Single(now);
            }else//Like Zhi
            {
                Single(now);Single(now);
            }
        }else
        {
            Single(now);
        }
    }
    Root=now;
}
Node *find(Node *now,int value)
{
    if(!now) return nullptr;
    if(value<now->value)
        if(now->left) return find(now->left,value);
        else return nullptr;
    else if(value>now->value)
        if(now->right) return find(now->right,value);
        else return nullptr;
    return now;
}
void insert(Node* &Root,Node *now,int value)
{
    if(!Root)
    {
        last_visit=Root=new Node(value);
        return;
    }
    if(value<now->value)
        if(now->left) insert(Root,now->left,value);
        else last_visit=now->left=new Node(value,now);
    else if(value>now->value)
        if(now->right) insert(Root,now->right,value);
        else last_visit=now->right=new Node(value,now);
    else
    {
        now->cnt+=1;
        last_visit=now;
    }
}
bool del(Node* &Root,Node *now,int value)
{
    Node *will_del=find(Root,value);
    if(!will_del) return false;
    if(will_del->cnt>=2) return (bool)(1+(will_del->cnt--)*0);
    LetsGo(SPlay,will_del);
    if(will_del->left)
    {
        Node *index=will_del->left;
        while(index->right) index=index->right;
        index->right=will_del->right;
        if(will_del->right) will_del->right->father=index;
        Root=will_del->left;
        Root->father=nullptr;
    }else
    {
        Root=will_del->right;
        if(Root) Root->father=nullptr;  
    }
    delete will_del;
    return true;
}
void Display(Node *now)
{
    if(!now)
    {
        putchar('^');
        return;
    }
    printf("%d(",now->value);
    Display(now->left);putchar(',');
    Display(now->right);putchar(')');
}
int Depth(Node *now)    
{
    if(!now) return 0;
    return max(Depth(now->left),Depth(now->right))+1;
}
void Clear(Node *now)
{
    if(!now) return;
    Clear(now->left);
    Clear(now->right);
    delete now;
}
void init_all()
{
    Clear(SPlay);SPlay=nullptr;
}
void Split(Node *A,Node *B){}
void Join(Node *A,Node *B){}
int GetNumber()
{
    return rand()%10000+1;
}
int main()
{
    srand((unsigned)time(0));
    for(int i=1;i<=5000;i+=1)
    {
        int x=GetNumber();
        insert(SPlay,SPlay,x);LetsGo(SPlay,last_visit);
    }
    printf("%d\n",Depth(SPlay));
    for(int i=1;i<=10000;i+=1) while(del(SPlay,SPlay,i));
    if(SPlay==nullptr) puts("Done!");
    return 0;
}