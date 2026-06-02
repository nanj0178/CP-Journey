#include <bits/stdc++.h>
using namespace std;
struct LCA {
    int _n;
    int log_h;
    vector<vector<int>> st;
    vector<int> _dep;
    vector<int> _par;
    LCA() {
    }
    void init(vector<int>& d, vector<int>& par) {
        _dep = d;
        _par = par;
        build();
    }
    void build() {
        _n = _par.size();
        log_h = __lg(_n) + 1;
        st.assign(log_h, vector<int>(_n));

        for (int i = 0; i < _n; i++) {
            st[0][i] = _par[i];
        }

        for (int i = 1; i < log_h; i++) {
            for (int j = 0; j < _n; j++) {
                st[i][j] = st[i - 1][st[i - 1][j]];
            }
        }
    }

    int move(int cur, int dis) {
        if (dis == 0) return cur;
        for(int i = log_h - 1; i >= 0; i--) {
            if ((1 << i) <= dis) {
                dis -= (1 << i);
                cur = st[i][cur];
            }
        }
        return cur;
    }       
    int findlca(int a, int b) {
        for(int i = log_h - 1; i >= 0; i--) {
            if (st[i][a] != st[i][b]) {
                a = st[i][a];
                b = st[i][b];
            }
        }
        return st[0][a];
    }    
    int getLca(int a, int b) {
        if (_dep[a] < _dep[b]) {
            swap(a, b);
        }
        a = move(a, _dep[a] - _dep[b]);
        if (a == b) {
            return a;
        }
        return findlca(a, b);
    }  
    int getDis(int a, int b) {
        int lca = getLca(a, b);
        int dis = _dep[a] + _dep[b] - 2 * _dep[lca];
        return dis;
    }
}lca;
// O(lgn)
// init:
//     node 0 is null point, 1 ~ n is normal tree node
//     d: depth
//     par: parent
//     lca.init(d, par);