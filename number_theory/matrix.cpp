#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>

namespace matrix {
    using namespace std;

    typedef int64_t ll;

    ll mod = -1; // -1 means no mod, set this value to use mod

    // 1-indexed
    class matrix {
        int n, m;
        vector< vector<ll> > data;

    public:
        inline void set_zero() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    data[i][j] = 0;
                }
            }
        }

        inline void set_identity() {
            if (n != m) {
                throw invalid_argument("Matrix is not square");
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    data[i][j] = (i == j);
                }
            }
        }

        matrix(int n, int m) : n(n), m(m), data(n, vector<ll>(m)) {
            if (n == m) {
                set_identity();
            } else {
                set_zero();
            }
        }
        matrix(const matrix& other) : n(other.n), m(other.m), data(other.data) {}

        inline void set(int i, int j, ll val) {
            data[i - 1][j - 1] = val;
        }

        inline ll get(int i, int j) const {
            return data[i - 1][j - 1];
        }

        inline void print() const {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << data[i][j] << " ";
                }
                cout << endl;
            }
        }

        matrix operator*(const matrix& other) const {
            if (m != other.n) {
                throw invalid_argument("Matrix dimensions do not match");
            }

            matrix res(n, other.m);
            res.set_zero();
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < other.m; j++) {
                    for (int k = 0; k < m; k++) { // m == other.n
                        res.data[i][j] += data[i][k] * other.data[k][j];
                        if (mod != -1) {
                            res.data[i][j] %= mod;
                        }
                    }
                }
            }
            return res;
        }

        matrix operator^(ll k) const {
            matrix res(n, n);
            matrix base(*this);
            res.set_identity();

            while (k > 0) {
                if (k & 1) {
                    res = res * base;
                }
                base = base * base;
                k >>= 1;
            }
            return res;
        }
    };
}