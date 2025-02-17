#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=305;
int p,ll[maxn],lr[maxn];
bool vis[maxn];
vector<int> G[maxn];
bool find(int x)
{
	for(int i=0;i<G[x].size();i++)
	{
		int to=G[x][i];
		if(!vis[to])
		{
			vis[to]=true;
			if(!lr[to]||find(lr[to]))
			{
				ll[x]=to;
				lr[to]=x;
				return true;
			}
		}
	}
	return false;
}
void init()
{
	for(int i=1;i<=p;i++) G[i].clear();
}
void Demo()
{
    init();
    int ans=0;
    memset(ll,0,sizeof(ll));
	memset(lr,0,sizeof(lr));
    for(int i=1;i<=p;i++)
    {
        if(!ll[i])
        {
            memset(vis,0,sizeof(vis));
            if(find(i)) ans++;
        }
    }
}
int main()
{
	return 0;
}