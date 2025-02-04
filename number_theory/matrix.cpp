#include <algorithm>
#include <cstdint>
#include <vector>
#include <cmath>

namespace matrix {
    using namespace std;

    typedef int64_t ll;

    // 1-indexed
    class matrix {
        int n, m;
        vector< vector<ll> > data;

    public:
        matrix(int n, int m) : n(n), m(m), data(n, vector<ll>(m)) {}

        inline void set(int i, int j, ll val) {
            data[i - 1][j - 1] = val;
        }

        inline ll get(int i, int j) const {
            return data[i - 1][j - 1];
        }

        matrix operator*(const matrix& other) const {
            matrix res(n, other.m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < other.m; j++) {
                    for (int k = 0; k < m; k++) { // m == other.n
                        res.data[i][j] += data[i][k] * other.data[k][j];
                    }
                }
            }
            return res;
        }
    };
}