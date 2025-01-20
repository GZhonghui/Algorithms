/*

割点和割边（桥）
图必须是无向图 可以存在重边

参考资料：
https://oi-wiki.org/graph/cut/
https://www.cnblogs.com/nullzx/p/7968110.html

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
typedef int64_t ll;

class Cut {
    struct Edge {
        int u, v, id; // u -> v, id
    };
    
    int n, m;
    vector< vector<int> > g;
    vector<Edge> edges;

    vector<int> dfn, low, father;
    vector<bool> vis, is_cut_point, is_cut_edge;
    int idx, cnt_cut_points, cnt_cut_edges;

public:
    void init(int n, int m) { // [1, n]
        this->n = n;
        this->m = m;
        edges.clear();
        g.resize(n + 1);
        for(int i = 0; i <= n; i++) {
            g[i].clear();
        }
    }

    void add_edge(int u, int v, int id) { // edge id: [1, m]
        edges.push_back((Edge){u, v, id});
        g[u].push_back(edges.size() - 1);
        edges.push_back((Edge){v, u, id});
        g[v].push_back(edges.size() - 1);
    }

protected:
    // from: https://oi-wiki.org/graph/cut/
    void tarjan_p(int u, int fa) {  // u 当前点的编号，fa 自己爸爸的编号
        vis[u] = true;              // 标记
        low[u] = dfn[u] = ++idx;    // 打上时间戳
        int child = 0;              // 每一个点儿子数量
        for (int k : g[u]) {        // 访问这个点的所有邻居 （C++11）
            int v = edges[k].v;
            if (!vis[v]) {
                child++;                       // 多了一个儿子
                tarjan_p(v, u);                // 继续
                low[u] = min(low[u], low[v]);  // 更新能到的最小节点编号
                if (fa != u && low[v] >= dfn[u] && !is_cut_point[u]) {  // 主要代码
                    // 如果不是自己，且不通过父亲返回的最小点符合割点的要求，并且没有被标记过
                    // 要求即为：删了父亲连不上去了，即为最多连到父亲
                    is_cut_point[u] = true;
                    cnt_cut_points++;  // 记录答案
                }
            } else if (v != fa) {
                // 如果这个点不是自己的父亲，更新能到的最小节点编号
                low[u] = min(low[u], dfn[v]);
            }
        }
        // 主要代码，自己的话需要 2 个儿子才可以
        if (fa == u && child >= 2 && !is_cut_point[u]) {
            is_cut_point[u] = true;
            cnt_cut_points++;  // 记录答案
        }
    }

    // from: https://oi-wiki.org/graph/cut/
    void tarjan_e(int u, int fa, vector<int> &cut_edges) {
        bool flag = false;
        father[u] = fa;
        low[u] = dfn[u] = ++idx;
        for (int k : g[u]) {
            int v = edges[k].v;
            if (!dfn[v]) {
                tarjan_e(v, u, cut_edges);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    is_cut_edge[v] = true;
                    cnt_cut_edges++;
                    cut_edges.push_back(edges[k].id);
                }
            } else {
                if (v != fa || flag)
                    low[u] = min(low[u], dfn[v]);
                else
                    flag = true;
            }
        }
    }

public:
    void calc_cut_points(vector<int> &cut_points) {
        dfn = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        vis = vector<bool>(n + 1, false);
        is_cut_point = vector<bool>(n + 1, false);
        cnt_cut_points = 0;

        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                idx = 0;
                tarjan_p(i, i);
            }
        }

        cut_points.clear();
        for(int i = 1; i <= n; i++) {
            if(is_cut_point[i]) {
                cut_points.push_back(i);
            }
        }
    }

    void calc_cut_edges(vector<int> &cut_edges) {
        dfn = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        father = vector<int>(n + 1, 0);
        // is_cut_edge[x] == true -> (x, father[x]) is a cut edge
        is_cut_edge = vector<bool>(n + 1, false);
        cnt_cut_edges = 0;

        cut_edges.clear();
        for(int i = 1; i <= n; i++) {
            if(!dfn[i]) {
                idx = 0;
                tarjan_e(i, i, cut_edges);
            }
        }        
    }
};

void test_cut() {
    Cut cut;
    cut.init(5, 5);
    cut.add_edge(1, 2, 1);
    cut.add_edge(2, 3, 2);
    cut.add_edge(2, 3, 3); // 重边
    cut.add_edge(3, 4, 4);
    cut.add_edge(4, 5, 5);

    vector<int> cut_points;
    cut.calc_cut_points(cut_points); // 2 3 4
    for(int i = 0; i < cut_points.size(); i++) {
        cout << cut_points[i] << " ";
    }
    cout << endl;

    vector<int> cut_edges;
    cut.calc_cut_edges(cut_edges); // 1 4 5
    for(int i = 0; i < cut_edges.size(); i++) {
        cout << cut_edges[i] << " ";
    }
    cout << endl;
}