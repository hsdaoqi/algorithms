//tarjan算法求割点
//割点：对于一个无向图，如果把一个点删除后，联通块的个数增加了，那么这个点就是割点
//割点判定法则：
//1.如果x不是根节点，当搜索树上存在x的一个子节点y，满足low[y]>=dfn[x],那么x就是割点
//2.如果x是根节点，当搜索树上存在至少两个子节点y1,y2,满足上述条件，那么x就是割点


struct CUTP {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, low,cut;
    int cur;

    CUTP() {}
    CUTP(int _n):n(_n) {
        init(_n);
    }

    void init(int _n) {
        adj.assign(_n, {});
        dfn.assign(_n, 0);
        low.resize(_n);
        cut.resize(_n);
        cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int x,int &root) {
        dfn[x] = low[x] = ++cur;
        int child = 0;
        for (int y : adj[x]) {
            if (dfn[y] == 0) {
                dfs(y,root);
                low[x] = std::min(low[x], low[y]);
                if(low[y]>=dfn[x]){
                    child++;
                    if(x!=root||child>1){
                        cut[x]=1;
                    }
                }
            }else{
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }
    void work() {
        for (int i = 1; i < n; i++) {
            if (dfn[i] == 0) {
                dfs(i,i);
            }
        }
    }
};