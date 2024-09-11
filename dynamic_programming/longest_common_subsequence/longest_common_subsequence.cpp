#include <algorithm>

const int MAXN = 1e4 + 8;
const int MAXM = 1e4 + 8;

int a[MAXN], b[MAXM], f[MAXN][MAXM], n, m;

// 来源：OI-Wiki
// a[1,n] b[1,m]
int dp() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i] == b[j])
        f[i][j] = f[i - 1][j - 1] + 1;
      else
        f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
  return f[n][m];
}