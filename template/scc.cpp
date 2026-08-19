#include <bits/stdc++.h>
using namespace std;
const int SIZE = 200001;
vector<vector<int>> G;
vector<int> dfn;
vector<int> low;
vector<int> compId;
stack<int> stk;
bool instk[SIZE];
int dfsid;
int compCnt;
vector<int> compSize;
vector<set<int>> dag;
vector<int> endless;
vector<int> vis;
void tarjan(int cur) {
    dfsid++;
    low[cur] = dfn[cur] = dfsid;

    stk.push(cur);
    instk[cur] = true;
    
    for(auto next : G[cur]) {
        if (dfn[next] && !instk[next]) continue;
        if (dfn[next] == 0) tarjan(next);
        low[cur] = min(low[cur], low[next]);
    }
    if (dfn[cur] == low[cur]) {
        int last = -1;
        compCnt++;
        do {
            last = stk.top();stk.pop();
            instk[last] = false;
            compId[last] = compCnt;
        } while(last != cur);
    }
}
void buildCondensedGraph(int n) {
    dag.assign(compCnt + 1, {});
    compSize.assign(compCnt + 1, 0);
    for(int i = 1;i <= n; i++) {
        int id = compId[i];
        compSize[id]++;
    }
    for(int i = 1;i <= n; i++) {
        for(auto next : G[i]) {
            int x = compId[i];
            int y = compId[next];
            if (x != y) {
                dag[x].insert(y);
            }
        }
    }
}
void DAGserach(int cur) {
    endless[cur] = 0;
    vis[cur] = 1;
    if (compSize[cur] > 1) {
        endless[cur] = 1;
    }
    for(auto next : dag[cur]) {
        if (vis[next] == 0) {
            DAGserach(next);
        }
        endless[cur] |= endless[next];
    }
    return;
}
void solve() { 
    int n, m;
    cin >> n >> m;
    G.assign(n + 1, {});
    dfn.assign(n + 1, 0);
    low.assign(n + 1, 0);
    memset(instk, 0, sizeof(instk));
    dfsid = 0;
    compId.assign(n + 1, 0);
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }
    for(int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }
    buildCondensedGraph(n);
    endless.assign(compCnt + 1, 0);
    vis.assign(compCnt + 1, 0);
    for(int i = 1; i <= compCnt; i++) {
        if (vis[i]) continue;
        DAGserach(i);
    }
    int ans = 0;
    for(int i = 1; i <= compCnt; i++) {
        if (endless[i]) {
            ans += compSize[i];
        }
    }
    cout << ans << "\n";
}
// vertex id is 1-based.
// todo: update to struct or class