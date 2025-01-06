template<class T>
struct LineTree {
    int n ;
    struct line {
        T x1, x2, y;
        int tag;
        bool operator<(line &t) { return y < t.y; }
    };
    struct tree {
        int l, r,cnt;
        T len;
    };
    std::vector<line> L;
    std::vector<tree> tr;
    std::vector<T> X;
    std::vector<std::tuple<T,T,T,T>> doc;
    LineTree(int _n=2e5){
        init(_n+5);
    }
    void init(int _n){
        this->n=_n;
        L.resize(n);
        tr.resize(n*8);
        X.resize(n);
        doc.resize(1);
    }
    void add(T x1,T y1,T x2,T y2){
        doc.emplace_back(x1,y1,x2,y2);
    }
    T work(){
        for(int i=1;i<doc.size();i++){
            auto &[x1,y1,x2,y2]=doc[i];
            L[i]={x1,x2,y1,1};
            L[i+doc.size()-1]={x1,x2,y2,-1};
            X[i]=x1,X[i+doc.size()-1]=x2;
        }
        sort(L.begin()+1, L.end());
        sort(X.begin()+1, X.end());
        int tot = unique(X.begin()+1, X.end()) - X.begin();
        build(1, 1, tot - 2);
        T ans = 0;
        for (int i = 1; i < n; i++) {
            int l = lower_bound(X.begin()+1, X.begin()+tot, L[i].x1) - X.begin();
            int r = lower_bound(X.begin()+1, X.begin()+tot, L[i].x2) - X.begin();
            apply(1, l, r - 1, L[i].tag);
            ans += tr[1].len *1.0*1ll*(L[i + 1].y - L[i].y);
        }
        return ans;
    }
    void build(int u, int l, int r) {
        tr[u] = {l, r, 0, 0};
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void pushup(int u) {
        int l = tr[u].l, r = tr[u].r;
        if (tr[u].cnt) tr[u].len = X[r + 1] - X[l];
        else tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    void apply(int u, int l, int r, int tag) {
        if (l > tr[u].r || r < tr[u].l) return;
        if (l <= tr[u].l && r >= tr[u].r) {
            tr[u].cnt += tag;
            pushup(u);
            return;
        }
        apply(u << 1, l, r, tag);
        apply(u << 1 | 1, l, r, tag);
        pushup(u);
    }
};