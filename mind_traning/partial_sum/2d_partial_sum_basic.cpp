// https://atcoder.jp/contests/typical90/tasks/typical90_cc
// 基础二维前缀和

#include<algorithm>
#include<iostream>
#include<cstring>

const int maxn = 2e5+1;
const int maxk = 5e3+1;

int n,k,a[maxn],b[maxn],map[maxk][maxk],sum[maxk][maxk];

int search(int aa,int bb)
{
    if(aa < 1 || bb < 1) return 0;
    if(sum[aa][bb] != -1) return sum[aa][bb];

    int ans = map[aa][bb];
    if(aa > 1) ans += search(aa-1,bb);
    if(bb > 1) ans += search(aa,bb-1);
    if(aa > 1 && bb > 1) ans -= search(aa-1,bb-1);

    return sum[aa][bb] = ans;
}

int calc_sum(int x1, int y1, int x2, int y2)
{
    x2 = std::min(x2, maxk-1);
    y2 = std::min(y2, maxk-1);

    int ans = search(x2,y2) + search(x1-1,y1-1) - search(x2,y1-1) - search(x1-1,y2);
    
    return ans;
}

int main()
{
    memset(map,0,sizeof(int)*maxk*maxk);
    memset(sum,-1,sizeof(int)*maxk*maxk);

    std::cin >> n >> k;
    for(int i=1;i<=n;i+=1)
    {
        std::cin >> a[i] >> b[i];
        map[a[i]][b[i]] += 1;
    }
    search(maxk,maxk);

    int ans = 0;
    for(int i=1;i<maxk;i+=1)
    {
        for(int j=1;j<maxk;j+=1)
        {
            ans = std::max(ans, calc_sum(i,j,i+k,j+k));
        }
    }

    std::cout << ans << std::endl;

    return 0;
}