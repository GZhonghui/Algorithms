# （乘法）逆元

建议：如果只需要少数几个数字在一个固定模数下的逆元，不用自己计算，搜一下逆元计算器就可以了

> 模意义下乘法运算的逆元

## 扩展欧几里得法
原理是求解线性同余方程（Linear Congruence Equation）  
要求【被求逆元的数字】和【模数】互质

## 快速幂法
这种方法要求【模数是素数】（因为使用了费马小定理）

## 线性求逆元
在线性时间内，求出[1,n]内所有数字的逆元（比上面两种方法要快）