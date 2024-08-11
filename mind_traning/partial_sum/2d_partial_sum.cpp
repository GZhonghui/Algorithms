// 2维前缀和
// https://atcoder.jp/contests/typical90/tasks/typical90_ab

// 二次元いもす法

// https://x.com/e869120/status/1388262816101007363/photo/1
// 这题挺经典的
// 或许2维线段树也可以
// 卡了挺久的，为什么我的写法不可以？数据范围搞错了

#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<ctime>

namespace ac
{
    using namespace std;

    // Input
    int N;
    int lx[1 << 18], ly[1 << 18], rx[1 << 18], ry[1 << 18];

    // Count Number
    int cnt[1009][1009];
    int Answer[1 << 18];

    int ac_main() {
        // Step #1. Input
        // cin >> N;
        // for (int i = 1; i <= N; i++) cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];

        // Step #2. Imos Method in 2D
        for (int i = 1; i <= N; i++) {
            cnt[lx[i]][ly[i]] += 1;
            cnt[lx[i]][ry[i]] -= 1;
            cnt[rx[i]][ly[i]] -= 1;
            cnt[rx[i]][ry[i]] += 1;
        }
        for (int i = 0; i <= 1000; i++) {
            for (int j = 1; j <= 1000; j++) cnt[i][j] += cnt[i][j - 1];
        }
        for (int i = 1; i <= 1000; i++) {
            for (int j = 0; j <= 1000; j++) cnt[i][j] += cnt[i - 1][j];
        }

        // Step #3. Count Number
        for (int i = 0; i <= 1000; i++) {
            for (int j = 0; j <= 1000; j++) {
                if (cnt[i][j] >= 1) Answer[cnt[i][j]] += 1;
            }
        }

        // Step #4. Output The Answer
        // for (int i = 1; i <= N; i++) cout << Answer[i] << endl;
        return 0;
    }
}

const int maxn = 1010;
const int max_paper_size = 1e5+10;

int tag[maxn][maxn], sum[maxn][maxn], counter[max_paper_size]; // 原来是counter的大小搞错了

int dp(int x, int y)
{
    if(sum[x][y] != -1)
    {
        return sum[x][y];
    }

    int ans = -1;
    if(x == 1 && y == 1)
    {
        ans = tag[x][y];
    }else if(x == 1)
    {
        ans = tag[x][y] + dp(x, y-1);
    }else if(y == 1)
    {
        ans = tag[x][y] + dp(x-1, y);
    }else
    {
        ans = tag[x][y] + dp(x-1,y) + dp(x,y-1) - dp(x-1,y-1);
    }
    
    return sum[x][y] = ans;
}

int main()
{
    srand((unsigned)time(nullptr));

    memset(tag,0,sizeof(int)*maxn*maxn);
    memset(sum,-1,sizeof(int)*maxn*maxn);
    memset(counter,0,sizeof(int)*max_paper_size);

    int paper_count;
    
    paper_count = 1e5; // test
    scanf("%d",&paper_count);

    ac::N = paper_count;

    for(int i=1;i<=paper_count;i+=1)
    {
        int lx,ly,rx,ry;
        
        lx = rand() % 500;
        ly = rand() % 500;
        rx = lx + rand()%(999-lx) + 1;
        ry = ly + rand()%(999-ly) + 1;

        scanf("%d %d %d %d",&lx,&ly,&rx,&ry);

        ac::lx[i] = lx;
        ac::ly[i] = ly;
        ac::rx[i] = rx;
        ac::ry[i] = ry;

        tag[lx+1][ly+1] += 1;
        tag[rx+1][ry+1] += 1;

        tag[lx+1][ry+1] -= 1;
        tag[rx+1][ly+1] -= 1;
    }

    ac::ac_main();

    dp(maxn -1, maxn -1);

    for(int i=1;i<maxn;i+=1)
    {
        for(int j=1;j<maxn;j+=1)
        {
            int _value = dp(i,j);
            if(_value < 0 || _value >= maxn)
            {
                // printf("error at (%d,%d) value = %d\n",i,j,_value);
            }
            counter[dp(i,j)] += 1;
        }
    }

    bool found_error = false;
    for(int i=1;i<=paper_count;i+=1)
    {
        if(ac::Answer[i] != counter[i])
        {
            found_error = true;
            break;
        }
        printf("%d\n",counter[i]);
    }

    // printf("%s\n",found_error?"WA":"AC");

    return 0;
}
