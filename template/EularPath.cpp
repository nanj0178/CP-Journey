#include <bits/stdc++.h>
using namespace std;
// each edge go through once
vector<vector<array<int,2>>> E; // E[x] record [{target, id}]
vector<int> used;
vector<int> path;
void EularPath(int cur) {
    while(!E[cur].empty()) {
        auto [next, id] = E[cur].back();
        E[cur].pop_back();
        if (used[id]) continue;
        used[id] = 1;
        path.push_back(id);
        EularPath(next);
    }
}