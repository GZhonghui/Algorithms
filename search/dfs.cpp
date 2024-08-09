// https://atcoder.jp/contests/typical90/tasks/typical90_af

#include<iostream>
#include<cstdio>
#include<algorithm>

const int maxn = 11;
const int inf=0xffffff;

bool connect[maxn][maxn], used[maxn];
int assignment[maxn], data[maxn][maxn], n;

int dfs(int now, int cost)
{
    if(now >= n)
    {
        return cost;
    }

    int best = inf;
    for(int i=1;i<=n;i+=1)
    {
        if(!used[i] && ((now == 0) || (connect[assignment[now]][i])))
        {
            used[i] = true;
            assignment[now + 1] = i;
            int ans = dfs(now + 1, cost + data[i][now + 1]);
            used[i] = false;

            if(ans == -1) continue;

            best = std::min(best, ans);
        }
    }

    return (best == inf)? -1 : best;
}

int main()
{
    scanf("%d",&n);

    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=n;j+=1)
        {
            connect[i][j]=true;
            scanf("%d",&(data[i][j]));
        }
    }

    int m;
    scanf("%d",&m);

    for(int i=0;i<m;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        connect[x][y] = connect[y][x] = false;
    }

    for(int i=1;i<=n;i+=1)
    {
        used[i] = false;
    }

    printf("%d",dfs(0, 0));

    return 0;
}