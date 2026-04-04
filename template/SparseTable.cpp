#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SparseTable {
    // 0-based, [0, n)
    int _n;
    int log_h;
    vector<vector<T>> st;
    SparseTable(const vector<T>& a) {
        _n = a.size();
        log_h = __lg(_n) + 1;
        st.assign(log_h, vector<T>(_n));

        for (int i = 0; i < _n; i++) {
            st[0][i] = a[i];
        }

        for (int i = 1; i < log_h; i++) {
            for (int j = 0; j + (1 << i) <= _n; j++) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        assert(l < r);
        int h = __lg(r - l);
        return max(st[h][l], st[h][r - (1 << h)]);
    }
};