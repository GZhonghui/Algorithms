// https://codeforces.com/gym/102566/problem/F Magic Wand

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
using namespace std;
const int maxn=1e5+10;
int input[maxn];
int tree[maxn<<2];
int Left,Right,pos;
void build(int node,int l,int r)
{
    if(l==r)
        tree[node]=0;
    else
    {
        int mid=(l+r)>>1;
        build(node<<1,l,mid);
        build(node<<1|1,mid+1,r);
        tree[node]=0;
    }
}
int ask(int node,int l,int r)
{
    if(Left<=l&&r<=Right)
        return tree[node];
    int mid=(l+r)>>1;
    int sum=0;
    if(Left<=mid) sum+=ask(node<<1,l,mid);
    if(Right>=mid+1) sum+=ask(node<<1|1,mid+1,r);
    return sum;
}
void update(int node,int l,int r)
{
    if(l==r)
        tree[node]+=1;
    else
    {
        int mid=(l+r)>>1;
        if(pos<=mid) update(node<<1,l,mid);
        else if(pos>=mid+1) update(node<<1|1,mid+1,r);
        tree[node]=tree[node<<1]+tree[node<<1|1];
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        long long sum=0;
        vector<int> numbers;
        unordered_map<int,int> M;
        scanf("%d",&n);
        for(int i=1;i<=n;i+=1)
        {
            scanf("%d",&input[i]);
            numbers.push_back(input[i]);
        }
        sort(numbers.begin(),numbers.end());
        int index=0;
        for(int i=1;i<=numbers.size();i+=1)
        {
            int now=numbers[i-1];
            if(M.count(now))
                continue;
            M[now]=++index;
        }
        build(1,1,Right=++index);
        for(int i=1;i<=n;i+=1)
        {
            Left=M[input[i]]+1;
            sum+=8*ask(1,1,index);
            pos=M[input[i]];
            update(1,1,index);
        }
        printf("%lld\n",sum);
    }
    return 0;
}