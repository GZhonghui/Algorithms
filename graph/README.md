# 图论

- lowest_common_ancestor 最近公共祖先
- Tarjan (Tarjan's strongly connected components algorithm) 强连通分量
- Eulerian path (Eulerian graph) 欧拉回路，一笔画问题
- bipartite graph 二分图相关

## 函数图 Functional Graph
一种特殊的有向图（Directed Graph），其中每个节点恰好有一个出边（out-degree = 1）  
出边唯一性：每个节点  v  恰好有一条出边连接到另一个节点（就像连到父亲节点）  
无孤立点：因为每个节点都有出边，所以整个图中不会有孤立节点  
每一个联通分量中，一定存在一个环，把这个环缩成一个顶点的话，联通分量就会变成一棵树，环形成的点就是根  
在函数图中，可以使用并查集找环  
例题：  
- **Reachability in Functional Graph** https://atcoder.jp/contests/abc357/tasks/abc357_e
- **Count Arrays** https://atcoder.jp/contests/abc387/tasks/abc387_f