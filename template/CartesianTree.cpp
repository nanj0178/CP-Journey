#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL INF = 1e18;
struct CartesianTree {
    int n;
    vector<int> L, R, par, childCnt, cost;
    int root;

    CartesianTree(const vector<int>& a, const vector<int>& _cost) {
        cost = _cost;
        n = a.size();
        L.assign(n, -1);
        R.assign(n, -1);
        par.assign(n, -1);
        stack<int> s; // store index

        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!s.empty() && a[s.top()] > a[i]) {
                last = s.top();
                s.pop();
            }

            if (!s.empty()) {
                R[s.top()] = i;
                par[i] = s.top();
            }
            
            if (last != -1) {
                L[i] = last;
                par[last] = i;
            }
            
            s.push(i);
        }

        while (!s.empty()) {
            root = s.top();
            s.pop();
        }
    }
    vector<LL> cal() {
        childCnt.assign(n, 0);
        return _cal(root);
    }
    vector<LL> _cal(int cur) {
        if (cur == -1) return vector<LL>{0};
        auto ldp = _cal(L[cur]);
        auto rdp = _cal(R[cur]);
        if (L[cur] != -1) {
            childCnt[cur] += childCnt[L[cur]];
        }
        if (R[cur] != -1) {
            childCnt[cur] += childCnt[R[cur]];
        }        
        childCnt[cur]++;        
        vector<LL> dp(childCnt[cur] + 1, INF);
        for(int i = 0; i < ldp.size(); i++) {
            for(int j = 0; j < rdp.size(); j++) {
                dp[i + j + 1] = min(dp[i + j + 1], ldp[i] + rdp[j] + cost[cur]);
            }
        }
        for(int i = 0; i < ldp.size(); i++) {
            dp[i] = min(dp[i], ldp[i]);
        }
        for(int i = 0; i < rdp.size(); i++) {
            dp[i] = min(dp[i], rdp[i]);
        }    

        return dp;
    }
};