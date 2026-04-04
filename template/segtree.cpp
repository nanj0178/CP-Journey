#include <bits/stdc++.h>
using namespace std;
struct MinTrait {
    using Data = int;
    using Qdata = int;
    
    static Data default_value() { return 2e9; }
    
    static Data merge(const Data& x, const Data& y) {
        return min(x, y);
    }
    
    static bool good(const Data& x, const Qdata& v) {
        return x <= v;
    }
};
template <typename Trait>
struct Seg{
    using Data = typename Trait::Data;
    using Qdata = typename Trait::Qdata;    
    int _n;    
    vector<Data> node;

    Seg(int n) {
        _n = n;
        node.assign(4 * _n, Trait::default_value());
    }

    Seg(const vector<Data>& input) {
        _n = input.size();
        node.assign(4 * _n, Trait::default_value());
        _init(0, _n, 1, input);
    }    

    void pull(int id) {
        node[id] = Trait::merge(node[id * 2], node[id * 2 + 1]);
    }
    void _init(int L, int R, int id, const vector<Data> &input) {
        if(R - L == 1){
            node[id] = input[L];
            return;
        }
        int mm = L + (R - L) / 2;
        _init(L, mm, id * 2, input);
        _init(mm, R, id * 2 + 1, input);
        pull(id);
    }
    Data _qq(int L, int R, int id, int l, int r) {
        if(L >= l && R <= r) return node[id];
        int mm = L + (R - L) / 2;
        if(r <= mm) return _qq(L, mm, id * 2, l, r);
        if(l >= mm) return _qq(mm, R, id * 2 + 1, l, r);
        return Trait::merge(_qq(L, mm, id * 2, l, r), _qq(mm, R, id * 2 + 1, l, r));
    }
    Data query(int l, int r) {
        if (l >= r) return Trait::default_value();
        return _qq(0, _n, 1, l, r);
    }
    void _edit(int L, int R, int id, int p, Data v) {
        if(R - L == 1) {
            node[id] = v;
            return;
        }
        int mm = L + (R - L) / 2;
        if(p < mm) { _edit(L, mm, id * 2, p, v); }
        else { _edit(mm, R, id * 2 + 1, p, v); }
        pull(id);
    }
    void edit(int p, Data v) {
        _edit(0, _n, 1, p, v);
    }
    // binary search
    int _search(int L, int R, int id, const Qdata &v) {
        if(!Trait::good(node[id], v)) return -1;
        if(R - L == 1) return L;
         int mm = L + (R - L) / 2;
        int ret = _search(L, mm, 2 * id, v);
        if(ret != -1) return ret;
        return _search(mm, R, id * 2 + 1, v);
    }    
    int search(const Qdata &v) {
        return _search(0, _n, 1, v);
    }
};