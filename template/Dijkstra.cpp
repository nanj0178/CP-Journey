#include <bits/stdc++.h>
using namespace std;
using LL = long long;
struct Dijkstra {
    const LL INF = 1e18;
    int _n;
    vector<vector<array<LL,2>>> adj;
    vector<LL> dis;
    vector<int> par;
    Dijkstra(int n) : _n(n), adj(n), dis(n, INF), par(n, -1) {}

    void addE(int u, int v, LL w, bool dir = false) {
        adj[u].push_back({v, w});
        if (!dir) {
            adj[v].push_back({u, w});
        }
    }

    void run(int start) {
        fill(dis.begin(), dis.end(), INF);
        fill(par.begin(), par.end(), -1);
        
        priority_queue<array<LL,2>, vector<array<LL,2>>, greater<array<LL,2>>> pq;
        
        dis[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [cost, id] = pq.top(); pq.pop();
            if (cost > dis[id]) continue;
            for (auto &[next, w] : adj[id]) {
                if (cost + w < dis[next]) {
                    dis[next] = cost + w;
                    par[next] = id;
                    pq.push({cost + w, next});
                }
            }
        }
    }

    vector<int> getPath(int target) {
        if (dis[target] == INF) return {};
        vector<int> path;
        int cur = target;
        while(cur != -1) {
            path.push_back(cur);
            cur = par[cur];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};