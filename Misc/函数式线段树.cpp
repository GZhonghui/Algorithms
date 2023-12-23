#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
const int maxn=1e5+10;
struct Node
{
    int lson,rson,sum;
};
vector<int> Roots;
Node Tree[maxn<<5];
int Cnt,N;
int _pos,_value,_left,_right;
int cnt_num,Q,Values[maxn],RevMap[maxn],RealNum[maxn];
unordered_map<int,int> _Map;
inline int newNode()
{
    return ++Cnt;
}
inline void pushup(int node)
{
    Tree[node].sum=Tree[Tree[node].lson].sum+Tree[Tree[node].rson].sum;
}
int build(int left,int right)
{
    int Now=newNode();Tree[Now].lson=Tree[Now].rson=Tree[Now].sum=0;
    if(left==right) return Now;
    int mid=(left+right)>>1;
    Tree[Now].lson=build(left,mid);
    Tree[Now].rson=build(mid+1,right);
    return Now;
}
int update(int souNode,int left,int right)
{
    int Now=newNode();Tree[Now].lson=Tree[Now].rson=Tree[Now].sum=0;
    if(left==right)
    {
        Tree[Now].sum=Tree[souNode].sum+_value;
        return Now;
    }
    int mid=(left+right)>>1;
    if(_pos<=mid)
    {
        Tree[Now].rson=Tree[souNode].rson;
        Tree[Now].lson=update(Tree[souNode].lson,left,mid);
    }else
    {
        Tree[Now].lson=Tree[souNode].lson;
        Tree[Now].rson=update(Tree[souNode].rson,mid+1,right);
    }
    pushup(Now);
    return Now;
}
int ask(int node,int left,int right)
{
    if(_left<=left&&right<=_right) return Tree[node].sum;
    int ans=0,mid=(left+right)>>1;
    if(_left<=mid) ans+=ask(Tree[node].lson,left,mid);
    if(_right>mid) ans+=ask(Tree[node].rson,mid+1,right);
    return ans;
}
int ask_kth(int node,int left,int right,int kth)
{
    if(kth>Tree[node].sum) return 0;
    int mid=(left+right)>>1;
    if(kth<=Tree[Tree[node].lson].sum) return ask_kth(Tree[node].lson,left,mid,kth);
    return ask_kth(Tree[node].rson,mid+1,right,kth-Tree[Tree[node].lson].sum);
}
int ask_range_kth(int leftNode,int rightNode,int left,int right,int kth)
{
    if(left==right) return left=right;
    int NowSum=Tree[rightNode].sum-Tree[leftNode].sum;
    if(kth>NowSum) return -1;
    int mid=(left+right)>>1;
    int lsonSum=Tree[Tree[rightNode].lson].sum-Tree[Tree[leftNode].lson].sum;
    if(kth<=lsonSum) return ask_range_kth(Tree[leftNode].lson,Tree[rightNode].lson,left,mid,kth);
    return ask_range_kth(Tree[leftNode].rson,Tree[rightNode].rson,mid+1,right,kth-lsonSum);
}
void init_all()
{
    Roots.clear();Roots.push_back(1);
    Cnt=cnt_num=0;
    _Map.clear();
}
void display(int version=1)
{
    int Root=Roots[version-1];
    for(int i=1;i<=N;i+=1)
    {
        _left=_right=i;
        printf("%d%c",ask(Root,1,N)," \n"[i==N]);
    }
    printf("total nodes:%d\n",Tree[Root].sum);
}
void demo()
{
    init_all();
    build(1,N=20);
    for(int i=1;i<=N;i+=1)
    {
        _pos=_value=i;
        Roots.push_back(update(Roots[Roots.size()-1],1,N));
    }
    for(int i=1;i<=N+1;i+=1) display(i);
}
int main()
{
    // freopen("in.txt","r",stdin);
    int T;scanf("%d",&T);while(T--)
    {
        init_all();
        scanf("%d %d",&N,&Q);
        build(1,N);
        for(int i=1;i<=N;i+=1)
        {
            scanf("%d",&Values[i]);RealNum[i]=Values[i];
        }
        sort(Values+1,Values+1+N);
        for(int i=1;i<=N;i+=1)
        {
            if(!_Map.count(Values[i]))
            {
                _Map[Values[i]]=++cnt_num;
                RevMap[cnt_num]=Values[i];
            }
        }
        for(int i=1;i<=N;i+=1)
        {
            _pos=_Map[RealNum[i]];_value=1;
            Roots.push_back(update(Roots[Roots.size()-1],1,N));
        }
        //for(int i=1;i<=Roots.size();i+=1) display(i);
        while(Q--)
        {
            int kth,left,right;
            scanf("%d %d %d",&left,&right,&kth);
            printf("%d\n",RevMap[ask_range_kth(Roots[left-1],Roots[right],1,N,kth)]);
        }
    }
    return 0;
}