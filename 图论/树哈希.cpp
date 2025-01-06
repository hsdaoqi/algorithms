//树哈希
struct TreeHash {
    using ull = unsigned long long;
    mt19937 rng;
    ull rg;
    int n;
    set<ull> doc; //多少个子树不能同构
    vector<bool> f; //每个子树是否是对称的
    vector<ull> h; //每个子树的哈希值
    vector<vector<int>> adj;
    TreeHash(){};
    TreeHash(vector<vector<int>> _adj){
        this->adj=_adj;
        this->n=adj.size();
        h.resize(n);
        f.resize(n);
        this->rng=mt19937((chrono::system_clock::now().time_since_epoch().count()));
        uniform_int_distribution<ull> dist(0,numeric_limits<ull>::max());
        this->rg=dist(rng);
        dfs(1,1);
    }
    ull shift(ull x) {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }
    void dfs(int u,int fa){
        ull res=rg;
        ull sum=0;
        for(int v:adj[u]){
            if(v==fa) continue;
            dfs(v,u);
            res+= shift(h[v]);
            sum^= shift(h[v]);
        }
        h[u]=res;
        doc.insert(res);
        if(sum==0) f[u]=1;
        else{
            for(int v:adj[u]){
                if(v==fa) continue;
                if(shift(h[v])==sum&&f[v]){
                    f[u]=1;
                    break;
                }
            }
        }
    }
};