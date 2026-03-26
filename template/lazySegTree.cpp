#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using Qdata = int;
struct Data {
    LL max_value;
    void init(LL x) {
        max_value = x;
    }
};
struct Tag {
    LL added;
    void init() {
        added = 0;
    }
};
struct Seg{
    vector<Data> node;
    vector<Tag> tag;
    int LLIMIT, RLIMIT;  
    Data _merge(const Data &x, const Data &y) {
        return {max(x.max_value, y.max_value)};
    }
    Data _apply(const Tag &tag, const Data &x) {
        return {x.max_value + tag.added};
    }
    Tag _combine(const Tag &x, const Tag &y) {
        return {x.added + y.added};
    }
    void initSetting(int size, int l, int r) {
        node.resize(4 * (size + 1));
        tag.resize(4 * (size + 1));
        LLIMIT = l;
        RLIMIT = r;
    }    
    void _push(int id){
        for(int nxt_id: {id * 2, id * 2 + 1}) {
            node[nxt_id] = _apply(tag[id], node[nxt_id]);
            tag[nxt_id] = _combine(tag[id], tag[nxt_id]);
        }
        tag[id].init();
    }
    void _pull(int id){
        node[id] = _merge(node[id * 2], node[id * 2 + 1]);
    }
    void _init(int L, int R, int id, vector<Data> &input){
        tag[id].init();
        if(L == R) {
            node[id] = input[L];
            return;
        }
        int mm = (L + R) / 2;
        _init(L, mm, id * 2, input);
        _init(mm + 1, R, id * 2 + 1, input);
        _pull(id);
    }
    void init(vector<Data> &input) {
        _init(LLIMIT, RLIMIT, 1, input);
    }    
    Data _qq(int L, int R, int id, int ll, int rr) {
        if(L >= ll && R <= rr) {
            return node[id];
        }
        int mm = (L + R) / 2;
        _push(id);
        if(mm >= rr) return _qq(L, mm, id * 2, ll, rr);
        if(mm < ll) return _qq(mm + 1, R, id * 2 + 1, ll, rr);
        return _merge(_qq(L, mm, id * 2, ll, rr), _qq(mm + 1, R, id * 2 + 1, ll, rr));
    }
    Data query(int l, int r) {
        return _qq(LLIMIT, RLIMIT, 1, l, r);
    }    
    void _update(int L, int R, int id, int ll, int rr, Tag v) {
        if(R < ll || L > rr) return;
        if(L >= ll && R <= rr) {
            node[id] = _apply(v, node[id]);
            tag[id] = _combine(v, tag[id]);
            return;
        }
        int mm = (L + R) / 2;
        _push(id);
        _update(L, mm, id * 2, ll, rr, v);
        _update(mm + 1, R, id * 2 + 1, ll, rr, v);
        _pull(id);
    }
    void update(int l, int r, Tag &v) {
        _update(LLIMIT, RLIMIT, 1, l, r, v);
    }    
    // binary search
    bool _good(Data x, Qdata &v) {
        // check condition
        return x.max_value != v;
    }
    int _search(int L, int R, int id, Qdata &v) {
        if(!_good(node[id], v)) return -1;
        if(L == R) return L;
        int mm = (L + R) / 2;
        _push(id);
        int ret = _search(L, mm, 2 * id, v);
        if(ret != -1) return ret;
        return _search(mm + 1, R, id * 2 + 1, v);
    }        
    int search(Qdata &v) {
        return _search(LLIMIT, RLIMIT, 1, v);
    }    
};