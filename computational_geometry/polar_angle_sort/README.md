# 极角排序 偏角ソート

- **极角排序** https://www.cnblogs.com/kingwz/p/16151120.html

## 什么是极角？
> 极角，指的就是以x轴正半轴为始边，逆时针转过的角，这个角的范围是[0,2π]。极角排序就是按极角大小排序...

## 基本思路
atan2计算出极角，再根据极角的大小排序即可

## 例题
- https://atcoder.jp/contests/typical90/tasks/typical90_i 从N个点中，找到3个点，使其组成的角度最大