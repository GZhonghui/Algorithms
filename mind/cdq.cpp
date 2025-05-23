/*

CDQ分治 cdq_divide_and_conquer

分治算法：Divide-and-conquer algorithm (分割統治法)

> CDQ 分治是一种思想而不是具体的算法，与**动态规划**类似  
> CDQ 分治的思想最早由 IOI2008 金牌得主陈丹琦在高中时整理并总结，它也因此得名。（怪不得没有英文翻译）

## 用途1：解决和点对有关的问题
> 找到这个序列的中点 $mid$  
> 将所有点对 $(i,j)$ 划分为 3 类  
> <1> $1 \leq i \leq mid,1 \leq j \leq mid$ 的点对；  
> <2> $1  \leq i \leq mid ,mid+1 \leq j \leq n$ 的点对；  
> <3> $mid+1 \leq  i \leq n,mid+1 \leq j \leq n$ 的点对。  
> 将 $(1,n)$ 这个序列拆成两个序列 $(1,mid)$ 和 $(mid+1,n)$。此时第一类点对和第三类点对都在这两个序列之中  
> 递归地处理这两类点对  
> 设法处理第二类点对

### 例题推荐
> 三维偏序是 CDQ 分治的经典问题。

## 用途2：1D 动态规划的优化与转移
## 用途3：通过 CDQ 分治，将一些动态问题转化为静态问题

*/

// TODO
namespace cdq {

} // namespace cdq