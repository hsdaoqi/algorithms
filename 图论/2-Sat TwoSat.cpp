struct TwoSat {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    std::vector<int> id, dfn, low;
    std::vector<int> stk;
    int now = 0, cnt = 0;
    TwoSat(int n) : n(n), e(2 * (n+1)), ans((n+1)) {
        id.assign(2*(n+1),-1);
        dfn.assign(2*(n+1),-1);
        low.assign(2*(n+1),-1);
    }
    void addClause(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    void addClause(int u,int v){
        e[u].push_back(v);
    }
    bool satisfiable() {
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;cnt++;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
            }
        };
        for (int i = 1; i <= 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        for (int i = 1; i <= n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};