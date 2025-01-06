template<class T>
struct ODT {
    struct node {
        int l, r;
        mutable T v;
        node(int l, int r, T v) : l(l), r(r), v(v) {};
        bool operator<(const node &x) const { return l < x.l; }
    };
    set<node> tr;
    T sum = 0;
    ODT(){};
    ODT(int l,int r,T v){
        init(l,r,v);
    }
    void init(int l,int r,T v){
        tr.clear();
        tr.insert(node(l,r,v));
        sum=(r-l+1)*v;
    }

    auto split(int pos) {
        auto it = tr.upper_bound(node(pos, 0, 0));
        it--;
        if (it->l == pos) return it;
        auto [l, r, v] = *it;
        tr.erase(it);
        tr.insert(node(l, pos - 1, v));
        return tr.insert(node(pos, r, v)).first;
    }

    void assign(int l, int r, T v) {
        auto ed = split(r + 1), st = split(l);//顺序不能颠倒
        for(auto it=st;it!=ed;it++){
            auto [ll,rr,vv]=*it;
            sum-=(rr-ll+1)*vv;
        }
        tr.erase(st, ed);//删除从[st,ed)
        tr.insert(node(l, r, v));
        sum+=(r-l+1)*v;
    }

    void rangeAdd(int l,int r,T v){
        auto ed= split(r+1);
        for(auto it= split(l);it!=ed;it++){
            it->v+=v;
        }
    }

    T rangeQuery(int l,int r){
        auto st= tr.upper_bound(node(l,0,0));
        st--;
        auto ed = tr.upper_bound(node(r,0,0));
        ed--;
        if(ed==st) return (r-l+1)*st->v;
        T tot=0;
        for(auto it=st;;it++){
            auto [ll,rr,vv]=*it;
            if(it==st) {
                tot+=(rr-l+1)*vv;
            }
            else if(it==ed){
                tot+=(r-ll+1)*vv;
                return tot;
            }else{
                tot+=(rr-ll+1)*vv;
            }
        }
    }

    T kth(int l,int r,int k){//区间第k大
        auto ed= split(r+1);
        vector<pair<T,int>> v;//存节点的值和区间长度
        for(auto it= split(l);it!=ed;it++){
            v.emplace_back(it->v,it->r-it->l+1);
        }
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i++){
            k-=v[i].second;
            if(k<=0) return v[i].first;
        }
    }

};