//无向图中极大的不包含割边的连通块被称为边双联通分量

struct EDCC {
    int n{};
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<std::vector<int>> ndcc;
    std::vector<std::tuple<int, int, int>> bri;
    std::vector<int> dfn, low, stk, bel;
    int cnt{}, cur{}, idx{};

    EDCC() = default;

    EDCC(int _n) : n(_n) {
        Init(_n);
    }

    void Init(int _n) {
        adj.assign(_n, {});
        ndcc.assign(_n, {});
        dfn.resize(_n);
        low.resize(_n);
        bel.resize(_n);
        cnt = cur = 0;
    }

    void addEdge(int u, int v) {
        idx++;
        adj[u].emplace_back(v, idx);
        adj[v].emplace_back(u, idx);
    }

    void dfs(int x, int fid) {
        dfn[x] = low[x] = ++cur;
        stk.push_back(x);
        for (auto [y, id]: adj[x]) {
            if (dfn[y] == 0) {
                dfs(y, id);
                low[x] = std::min(low[x], low[y]);
                if (low[y] > dfn[x]) {
                    bri.emplace_back(x, y, id);
                }
            } else if (id != fid) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            ++cnt;
            int y;
            do {
                y = stk.back();
                stk.pop_back();
                bel[y] = cnt;
                ndcc[cnt].push_back(y);
            } while (y != x);
        }
    }

    void work() {
        for (int i = 1; i < n; i++) {
            if (!dfn[i]) {
                dfs(i, i);
            }
        }
    }
};