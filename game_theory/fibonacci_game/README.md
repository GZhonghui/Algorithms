# 斐波那契博弈

有一堆物品，数量为n，两人轮流取，先手第一次可以取任意个但不能全部取完。  
之后每次取的数量必须**大于等于** $1$ 且**小于等于**上次（上次？应该指的是对手吧）取的数量的两倍，最后把物品全部取完者胜利

$n$ 为斐波那契数（出现在斐波那契数列中的数字）时，为必败状态

*fibonacci.cpp*