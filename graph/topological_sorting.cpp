/*

拓扑排序 topological sort

*/

#include <algorithm>
#include <cstdint>
#include <vector>
#include <queue>

namespace topological_sorting {
    using namespace std;
    
    class TopologicalSorting {
    protected:
        int n;
        vector< vector<int> > g;
        vector<int> in_degree;

    public:
        TopologicalSorting(int n) : n(n) { // id range: [1, n]
            g.resize(n + 1);
            in_degree = vector<int>(n + 1, 0);
        }

        void add_edge(int u, int v) {
            g[u].push_back(v);
            in_degree[v]++;
        }

        bool sort(vector<int> &ans) {
            ans.clear();

            queue<int> q;
            for (int i = 1; i <= n; i++) {
                if (in_degree[i] == 0) {
                    q.push(i);
                }
            }

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                ans.push_back(u);

                for (int v : g[u]) {
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        q.push(v);
                    }
                }
            }

            return ans.size() == n;
        }
    };
}