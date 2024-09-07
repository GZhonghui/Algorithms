// 由AI生成

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

const int MAXN = 500; // 较小的节点数，例如500
int dist[MAXN][MAXN];

void floydWarshall(int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices (<= " << MAXN << "): ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    // 初始化距离数组
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX;
        }
    }

    cout << "Enter the edges in the format: u v w" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // 因为是无向图
        dist[v][u] = min(dist[v][u], w);
    }

    floydWarshall(n);

    cout << "Distance matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
