#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using Qdata = int;
struct MaxAddTrait {
    using Data = long long;
    using Tag = long long;
    using Qdata = long long;

    static Data default_data() { return -4e18; } 
    static Tag default_tag() { return 0; }

    static Data merge(const Data &x, const Data &y) {
        return max(x, y);
    }

    static Data apply(const Tag &tag, const Data &x) {
        return x + tag;
    }

    static Tag combine(const Tag &new_tag, const Tag &old_tag) {
        return old_tag + new_tag;
    }

    static bool good(const Data &x, const Qdata &v) {
        return x != v; 
    }
};

template <typename Trait>
struct LazySeg {
    using Data = typename Trait::Data;
    using Tag = typename Trait::Tag;
    using Qdata = typename Trait::Qdata;
    
    int _n;
    vector<Data> node;
    vector<Tag> tag;

    LazySeg(int n) {
        _n = n;
        node.assign(4 * _n, Trait::default_data());
        tag.assign(4 * _n, Trait::default_tag());
    }

    LazySeg(const vector<Data>& input) {
        _n = input.size();
        node.assign(4 * _n, Trait::default_data());
        tag.assign(4 * _n, Trait::default_tag());
        _init(0, _n, 1, input);
    }

    void _pull(int id) {
        node[id] = Trait::merge(node[id * 2], node[id * 2 + 1]);
    }

    void _push(int id) {
        for(int nxt_id : {id * 2, id * 2 + 1}) {
            node[nxt_id] = Trait::apply(tag[id], node[nxt_id]);
            tag[nxt_id] = Trait::combine(tag[id], tag[nxt_id]);
        }
        tag[id] = Trait::default_tag();
    }

    void _init(int L, int R, int id, const vector<Data> &input) {
        if(R - L == 1) {
            node[id] = input[L];
            return;
        }
        int mm = L + (R - L) / 2;
        _init(L, mm, id * 2, input);
        _init(mm, R, id * 2 + 1, input);
        _pull(id);
    }

    void _update(int L, int R, int id, int l, int r, const Tag &v) {
        if(l <= L && R <= r) {
            node[id] = Trait::apply(v, node[id]);
            tag[id] = Trait::combine(v, tag[id]);
            return;
        }
        
        _push(id);
        int mm = L + (R - L) / 2;
        if(r <= mm) _update(L, mm, id * 2, l, r, v);
        if(l >= mm) _update(mm, R, id * 2 + 1, l, r, v);
        _pull(id);
    }

    void update(int l, int r, const Tag &v) {
        if (l >= r) return;
        _update(0, _n, 1, l, r, v);
    }

    Data _qq(int L, int R, int id, int l, int r) {
        if(l <= L && R <= r) {
            return node[id];
        }
        
        _push(id);
        int mm = L + (R - L) / 2;
        
        if(r <= mm) return _qq(L, mm, id * 2, l, r);
        if(l >= mm) return _qq(mm, R, id * 2 + 1, l, r);
        return Trait::merge(_qq(L, mm, id * 2, l, r), _qq(mm, R, id * 2 + 1, l, r));
    }

    Data query(int l, int r) {
        assert(l < r);
        return _qq(0, _n, 1, l, r);
    }

    int _search(int L, int R, int id, const Qdata &v) {
        if(!Trait::good(node[id], v)) return -1;
        if(R - L == 1) return L;
        
        _push(id);
        int mm = L + (R - L) / 2;
        
        int ret = _search(L, mm, 2 * id, v);
        if(ret != -1) return ret;
        return _search(mm, R, id * 2 + 1, v);
    }        

    int search(const Qdata &v) {
        return _search(0, _n, 1, v);
    }    
};