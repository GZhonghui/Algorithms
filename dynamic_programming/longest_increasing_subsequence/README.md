# 最长上升子序列

## 子序列和子串
子串（Substring）：原序列中**必须连续**的一段  
子序列（Subsequence）：原序列中**可以不连续**的一段  
注意：无论是子串和子序列，元素的顺序都是原序列中的顺序

## 常规思路
lis_01.cpp  
> dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度  

一维dp数组，思路简单，遍历两遍即可，时间复杂度：$O(N^2)$

## 优化：二分查找
lis_02.cpp  
优化后的时间复杂度：$O(N\log{N})$，思路查看Wiki

例题：
- lis_02.cpp: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_h
- lis_03.cpp: https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_x