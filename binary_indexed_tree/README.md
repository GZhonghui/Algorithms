# 树状数组 binary indexed tree

> 树状数组是一种支持 **单点修改**（只能加减？） 和 **区间查询**（只能查询和？） 的，代码量小的数据结构。

*binary_indexed_tree.cpp*（v2是封装的版本）  
树状数组，单点加减，求前缀和，速度比线段树快

*binary_indexed_tree_2d.cpp*（v2是封装的版本）  
二维树状数组，支持区间加减和区间查询

## 应用
- 求逆序对，时间复杂度是$O(N\log{N})$；并且目标区间可以动态维护。例题：[Another Shuffle Window](https://atcoder.jp/contests/abc380/tasks/abc380_g)