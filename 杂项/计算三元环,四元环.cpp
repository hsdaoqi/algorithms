i64 CalcThree(std::vector<std::pair<int, int>> &edges, int n) {
    std::vector<int> deg(n + 1);
    for (auto &[u, v]: edges) deg[u]++, deg[v]++;

    std::vector<std::vector<int>> adj(n + 1);
    for (auto &[u, v]: edges) {
        if (deg[u] > deg[v]) {
            std::swap(u, v);
        } else if ((deg[u] == deg[v] && u > v)) {
            std::swap(u, v);
        }
        adj[u].push_back(v);
    }

    i64 cnt = 0;
    std::vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) vis[j] = i;
        for (int j: adj[i]) {
            for (int k: adj[j]) {
                if (vis[k] == i) cnt++;
            }
        }
    }
    return cnt;
}


i64 CalcFour(std::vector<std::pair<int, int>> &edges, const int &n) {
    std::vector<int> deg(n + 1);
    std::vector<std::vector<int>> adj(n + 1), adj2(n + 1);

    for (auto &[u, v]: edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    auto cmp = [&](int i, int j) { return deg[i] > deg[j] || (deg[i] == deg[j] && i > j); };
    for (int i = 1; i <= n; i++) {
        for (int &j: adj[i]) {
            if (cmp(i, j)) adj2[i].push_back(j);
        }
    }

    i64 cnt = 0;
    std::vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int &j: adj2[i]) {
            for (int &k: adj[j]) {
                if (cmp(i, k)) cnt += vis[k]++;
            }
        }
        for (int &j: adj2[i]) {
            for (int &k: adj[j]) {
                if (cmp(i, k)) vis[k] = 0;
            }
        }
    }
    return cnt;
}