/*

最长公共子序列 longest common subsequence

子序列（Subsequence）：原序列中【可以不连续】的一段

1 2   3 4   5
  2 4 3 6 7 5
答案是：2 3 5

*/

#include <algorithm>

namespace longest_common_subsequence {

const int MAXN = 1e4 + 8; // 序列1的长度
const int MAXM = 1e4 + 8; // 序列2的长度

int a[MAXN], b[MAXM], f[MAXN][MAXM], n, m; // n, m 是序列1和序列2的长度

// 来源：OI-Wiki
// a[1,n] b[1,m] 1-indexed
// 朴素做法
int dp() {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (a[i] == b[j])
            f[i][j] = f[i - 1][j - 1] + 1;
        else
            f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
    }

    return f[n][m];
}

} // namespace longest_common_subsequence