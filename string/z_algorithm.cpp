/*

Z Algorithm 拓展KMP

类似前缀函数 也可以用来匹配所有子串

暂未验证正确性

*/

#include <iostream>
#include <vector>
#include <string>

// copied from: https://oi-wiki.org/string/z-func/
namespace z_algorithm {
    using namespace std;

    // 返回 z 数组 0-indexed
    // 对于一个长度为 n 的字符串 s
    // 定义函数 z[i] 表示 s 和 s[i,n-1]（即以 s[i] 开头的后缀）的最长公共前缀（LCP）的长度
    // 特别地，z[0] = 0
    vector<int> z_function(const string &s) {
        int n = (int)s.length();
        vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r && z[i - l] < r - i + 1) {
                z[i] = z[i - l];
            } else {
                z[i] = max(0, r - i + 1);
                while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            }
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return z;
    }
} // namespace z_algorithm

