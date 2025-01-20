/*

带权并查集
本代码是经典例题「POJ 1182 食物链」（http://poj.org/problem?id=1182）的代码
代码尚未整理 仅供参考

*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn=50001;
int n,k,fa[maxn],rel[maxn],relA,relB;
int root(int now)
{
    return fa[now]==now?now:root(fa[now]);
}
int rootRel(int now)
{
    int ans=0;
    int Final=root(now);
    while(now!=Final)
    {
        ans+=rel[now];
        ans%=3;
        now=fa[now];
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int ans=0,ins,x,y;
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++) fa[i]=i,rel[i]=0;
    while(k--)
    {
        scanf("%d %d %d",&ins,&x,&y);
        if(x>n||y>n){
            ans++;
        }
        else if(ins==1){
            if(root(x)==root(y))
            {
                relA=rootRel(x),relB=rootRel(y);
                if(relA!=relB) ans++;
            }else{
                relA=rootRel(x),relB=rootRel(y);
                rel[root(x)]=(6-relA-((3-relB)%3))%3;
                fa[root(x)]=root(y);

            }
        }else if(ins==2){
            if(x==y){
                ans++;
            }else{
                if(root(x)==root(y))
                {
                    relA=rootRel(x),relB=rootRel(y);
                    if((relA+((3-relB)%3))%3!=1) ans++;
                }else{
                    relA=rootRel(x),relB=rootRel(y);
                    rel[root(x)]=(7-relA-((3-relB)%3))%3;
                    fa[root(x)]=root(y);
                }
            }
        }
    }
    printf("%d",ans);
    return 0;
}