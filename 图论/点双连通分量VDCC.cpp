struct VDCC {
    int n{};
    std::vector<std::vector<int>> adj, dcc, ne;
    std::vector<int> dfn, low, cut, stk, id, bel;
    int cur{}, cnt{}, num{};

    VDCC() {}

    VDCC(int _n) : n(_n) {
        init(_n);
    }

    void init(int _n) {
        adj.assign(_n, {});
        dcc.assign(_n, {});
        dfn.assign(_n, 0);
        bel.assign(_n, 0);
        low.resize(_n);
        cut.resize(_n);
        cur = cnt = num = 0;
    }

    void addEdge(int u, int v) {
        if (u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void dfs(int x, int &root) {
        dfn[x] = low[x] = ++cur;
        stk.push_back(x);
        if (adj[x].empty()) {//孤立点
            dcc[++cnt].push_back(x);
            bel[x] = cnt;
            return;
        }
        int child = 0;
        for (int y: adj[x]) {
            if (dfn[y] == 0) {
                dfs(y, root);
                low[x] = std::min(low[x], low[y]);
                if (low[y] >= dfn[x]) {
                    child++;
                    if (x != root || child > 1) cut[x] = 1;
                    cnt++;
                    int z;
                    do {
                        z = stk.back();
                        bel[z] = cnt;
                        stk.pop_back();
                        dcc[cnt].push_back(z);
                    } while (z != y);
                    dcc[cnt].push_back(x);
                    bel[x] = cnt;
                }
            } else {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
    }

    void build() {
        if (ne.empty()) {
            ne.assign(2 * n, {});
            id.resize(n);
        }
        num = cnt;
        for (int i = 1; i < n; i++) {
            if (cut[i]) {
                id[i] = ++num;
                mp[num] = i;
            }
        }
        for (int i = 1; i <= cnt; i++) {
            for (int x: dcc[i]) {
                if (cut[x]) {
                    ne[i].push_back(id[x]);
                    ne[id[x]].push_back(i);
                }
            }
        }
    }

    void work() {
        for (int i = 1; i < n; i++) {
            if (dfn[i] == 0) {
                dfs(i, i);
            }
        }
    }
};