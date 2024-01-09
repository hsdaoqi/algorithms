struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low,siz,bel;
    int cur,cnt;

    SCC() {}
    SCC(int _n):n(_n) {
        init(_n);
    }

    void init(int _n) {
        adj.assign(_n, {});
        dfn.assign(_n, 0);
        low.resize(_n);
        siz.assign(_n,0);
        bel.assign(_n, 0);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int x) {
        dfn[x] = low[x] = ++cur;
        stk.push_back(x);

        for (int y : adj[x]) {
            if (dfn[y] == 0) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == 0) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;++cnt;
            do {
                y = stk.back();
                bel[y] = cnt;
                siz[cnt]++;
                stk.pop_back();
            } while (y != x);
        }
    }

    void work() {
        for (int i = 1; i < n; i++) {
            if (dfn[i] == 0) {
                dfs(i);
            }
        }
    }
};