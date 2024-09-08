// 代码来源：OI-Wiki

#include<vector>

using namespace std;

vector<int> breakdown(int N) {
  vector<int> result;
  for (int i = 2; i * i <= N; i++) {
    if (N % i == 0) {  // 如果 i 能够整除 N，说明 i 为 N 的一个质因子。
      while (N % i == 0) N /= i;
      result.push_back(i);
    }
  }
  if (N != 1) {  // 说明再经过操作之后 N 留下了一个素数
    result.push_back(N);
  }
  return result;
}

// 我们能够证明 result 中的所有元素均为 N 的素因数。
// 如果有一个素数表的话会更快