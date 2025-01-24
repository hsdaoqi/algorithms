template<typename T, typename Compare=std::less<>>
struct MST {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<T> val;
    std::vector<std::tuple<T, int, int>> E;
    std::vector<int> fa, doc, dep;
    std::vector<std::array<int, 25>> f;

    MST(int n_) : n(n_) {};

    void addEdge(int u, int v, T w) {
        E.emplace_back(w, u, v);
    }

    int find(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }

    T Kruskal(Compare comp = Compare()) {
        if (fa.empty())fa.assign(n, 0);
        iota(fa.begin(), fa.end(), 0);
        doc.clear();
        sort(E.begin(), E.end(), comp);
        T ans = 0;
        int cnt = 0;

        for (int i = 0; i < E.size(); i++) {
            auto [w, u, v] = E[i];
            int fu = find(u), fv = find(v);

            if (fu != fv) {
                fa[fu] = fv;
                doc.push_back(i);
                ans += w;
                cnt++;
            }
            if (cnt == n - 2) return ans;
        }
        return -1;
    }

    int KruskalRsTree() {
        fa.assign(2 * n - 2, 0);
        std::iota(fa.begin(), fa.end(), 0);
        adj.resize(2 * n - 2);
        val.resize(2 * n - 2);

        for (int i = 0; i < doc.size(); i++) {
            auto [w, u, v] = E[doc[i]];
            adj[n + i].emplace_back(find(u));
            adj[n + i].emplace_back(find(v));
            val[n + i] = w;
            fa[find(u)] = fa[find(v)] = n + i;
        }

        return n + doc.size() - 1;
    }

    void dfs(int u) {
        if (f.empty()) {
            f.assign(adj.size(), {});
            dep.assign(adj.size(), 1);
        }
        for (int i = 1; i <= std::__lg(dep[u]); i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int v: adj[u]) {
            if (v == fa[u]) continue;
            dep[v] = dep[u] + 1;
            f[v][0] = u;
            dfs(v);
        }
    }

    void work() {
        for (int i = 1; i < fa.size(); i++) {
            if (fa[i] == i) {
                dfs(i);
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) std::swap(u, v);
        for (int i = 24; i >= 0; i--) {
            if (dep[f[u][i]] >= dep[v]) {
                u = f[u][i];
            }
        }
        if (u == v) return v;

        for (int i = 24; i >= 0; i--) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i], v = f[v][i];
            }
        }
        return f[u][0];
    }

    T dist(int u, int v) {
        return val[lca(u, v)];
    }
};