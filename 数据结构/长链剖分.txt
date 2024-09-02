template<class T>
struct HLD {
    int n;
    std::vector<int> siz, top, parent, in, out, seq;
    std::vector<std::vector<std::pair<int, T>>> adj;
    std::vector<T> len, mx, dep;
    int cur;

    HLD() {}

    HLD(int n_) {
        init(n_);
    }

    void init(int _n) {//初始化
        this->n = _n;
        siz.resize(n);//子树大小
        top.resize(n);//重链的顶端
        dep.resize(n);//深度
        parent.resize(n);//父节点
        in.resize(n);//dfs序入
        out.resize(n);//dfs序出
        seq.resize(n);//记录dfsx序第几位是哪个节点
        mx.resize(n);//记录这条链的最深的深度
        len.resize(n);//这条链的长度
        cur = 0;
        adj.assign(n, {});
    }

    void addEdge(int u, int v, T w = 1) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void work(int root = 1) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        len[root] = mx[root];
        dfs2(root, 0);
    }

    void dfs1(int x) {
        for (auto &v: adj[x]) {
            auto [y, w] = v;
            if (y == parent[x]) continue;
            parent[y] = x;
            mx[y] = dep[y] = dep[x] + w;
            dfs1(y);
            if (adj[x][0].first == parent[x] || mx[y] >= mx[adj[x][0].first]) {
                mx[x] = mx[y];
                std::swap(v, adj[x][0]);
            }
        }
    }

    void dfs2(int u, T tw) {
        in[u] = ++cur;
        seq[cur] = u;
        for (auto [v, w]: adj[u]) {
            if (v == parent[u]) continue;
            top[v] = v == adj[u][0].first ? top[u] : v;
            len[v] = v == adj[u][0].first ? len[u] : mx[v] - dep[v] + w;
            dfs2(v, v == adj[u][0].first ? tw : w);
        }
        out[u] = cur;
    }
};
