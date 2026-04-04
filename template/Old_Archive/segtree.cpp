#include <bits/stdc++.h>
using namespace std;
using Qdata = int;
using Data = int;
struct Seg{
    vector<Data> node;
    int LLIMIT, RLIMIT;
    void initSetting(int size, int l, int r) {
        node.resize(4 * (size + 1));
        LLIMIT = l;
        RLIMIT = r;
    }
    Data merge(Data x, Data y) {
        return min(x, y);
    }

    void pull(int id) {
        node[id] = merge(node[id * 2], node[id * 2 + 1]);
    }
    void _init(int L, int R, int id, vector<Data> &input) {
        if(L == R){
            node[id] = input[L];
            return;
        }
        int mm = (L + R) / 2;
        _init(L, mm, id * 2, input);
        _init(mm + 1, R, id * 2 + 1, input);
        pull(id);
    }
    void init(vector<Data> &input) {
        _init(LLIMIT, RLIMIT, 1, input);
    }
    Data _qq(int L, int R, int id, int l, int r) {
        if(L >= l && R <= r) return node[id];
        int mm = (L + R) / 2;
        if(r <= mm) return _qq(L, mm, id * 2, l, r);
        if(l > mm) return _qq(mm + 1, R, id * 2 + 1, l, r);
        return merge(_qq(L, mm, id * 2, l, r), _qq(mm + 1, R, id * 2 + 1, l, r));
    }
    Data query(int l, int r) {
        return _qq(LLIMIT, RLIMIT, 1, l, r);
    }
    void _edit(int L, int R, int id, int p, Data v) {
        if(L == R) {
            node[id] = v;
            return;
        }
        int mm = (L + R) / 2;
        if(p <= mm) { _edit(L, mm, id * 2, p, v); }
        else { _edit(mm + 1, R, id * 2 + 1, p, v); }
        pull(id);
    }
    void edit(int p, Data v) {
        _edit(LLIMIT, RLIMIT, 1, p, v);
    }
    // binary search
    bool _good(Data x, Qdata &v) {
        return x >= v;
    }
    int _search(int L, int R, int id, Qdata &v) {
        if(!_good(node[id], v)) return -1;
        if(L == R) return L;
        int mm = (L + R) / 2;
        int ret = _search(L, mm, 2 * id, v);
        if(ret != -1) return ret;
        return _search(mm + 1, R, id * 2 + 1, v);
    }    
    int search(Qdata &v) {
        return _search(LLIMIT, RLIMIT, 1, v);
    }
};