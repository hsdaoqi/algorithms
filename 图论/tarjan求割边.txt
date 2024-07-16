//tarjan求割边
struct CUTB {
    int n;
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<std::pair<int, int>> bri;
    std::vector<int> dfn, low;
    int cnt, cur, idx;

    CUTB() {};

    CUTB(int _n) : n(_n) {
        Init(_n);
    }

    void Init(int _n) {
        adj.assign(_n, {});
        dfn.resize(_n);
        low.resize(_n);
        cnt = cur = idx = 0;
    }

    void addEdge(int u, int v) {
        idx++;
        adj[u].push_back({v, idx});
        adj[v].push_back({u, idx});
    }

    void dfs(int x, int fid) {
        dfn[x] = low[x] = ++cur;

        for (auto [y, id]: adj[x]) {
            if (dfn[y] == 0) {
                dfs(y, id);
                low[x] = std::min(low[x], low[y]);
                if (low[y] > dfn[x]) {
                    bri.emplace_back(x, y);
                }
            } else if (id != fid) {
                low[x] = std::min(low[x], dfn[y]);
            }
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