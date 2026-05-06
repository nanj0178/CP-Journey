#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct BinaryLifting {
    // 0-based, [0, n)
    int _n;
    int log_h;
    vector<vector<T>> st;
    BinaryLifting(const vector<T>& a) {
        _n = a.size();
        log_h = __lg(_n) + 1;
        st.assign(log_h, vector<T>(_n));

        for (int i = 0; i < _n; i++) {
            st[0][i] = a[i];
        }

        for (int i = 1; i < log_h; i++) {
            for (int j = 0; j < _n; j++) {
                st[i][j] = st[i - 1][st[i - 1][j]];
            }
        }
    }

    T query(int l, int r) {
        assert(l < r);
        int h = __lg(r - l);
        int cnt = 0;
        for(int i = h; i >= 0; i--) {
            if (st[i][l] <= r) {
                cnt += (1 << i);
                l = st[i][l];
            }
        }
        return cnt;
    }
};