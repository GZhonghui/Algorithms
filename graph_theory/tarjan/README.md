# Tarjan
Tarjan's strongly connected components algorithm  
强连通分量

> 【Wikipedia】在有向图的数学理论中，如果一个图的每一个顶点都可从该图其他任意一点到达，则称该**图是强连通**的。在任意有向图中**能够实现强连通的部分**我们称其为强连通分量。判断一个图是否为强连通以及找到一个图强连通分量只需要线性时间（Θ(V + E)）

> 【什么是强连通，强连通是定义在点对之间的】在本身可能**不是强连通的有向图**G中，如果一对顶点u和v之间在每个方向上都有一条路径，则称它们是强连通的。

> 强连通的二元关系是一个**等价关系**，其**等价类**的导出子图称为**强连通分量**。

> 如果将每个强连通分量收缩为单个顶点，则得到的图是一个**有向无环图**。

## 本算法在做什么？

输入一个有向图，计算其强连通分量（像是在说废话）