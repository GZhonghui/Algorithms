/*

KMP算法
给定一个文本 t 和一个字符串 s，我们尝试找到并展示 s 在 t 中的所有出现（occurrence）

暂未验证正确性

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// copied from: https://oi-wiki.org/string/kmp/
namespace kmp {
    using namespace std;

    // 计算前缀函数
    // 前缀函数 pi[i] 表示 s[0..i] 的最长公共真前后缀的长度
    void prefix_function(const string &s, vector<int> &pi) { // 0-indexed
        int n = (int)s.length();
        pi.resize(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
    }

    // KMP 算法的实现 ans is 0-indexed
    vector<int> find_occurrences(const string &text, const string &pattern) { // text 是文本串，一般来说是更长的一方
        string cur = pattern + '#' + text; // '#' 是分隔符，在 pattern 和 text 中都不存在
        int sz1 = text.size(), sz2 = pattern.size();
        vector<int> v, lps;
        prefix_function(cur, lps);
        for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
            if (lps[i] == sz2) v.push_back(i - 2 * sz2);
        }
        return v;
    }

} // namespace kmp