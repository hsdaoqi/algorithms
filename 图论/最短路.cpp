//变形
//1.最长路。把所有边取相反数即可
//2.乘积最大，边权相乘，可以通过取对数转化为加法。
//3.如果是单向边，求所有点到某一个的距离，可以反向建边，然后跑dijkstra
//4.分层最短路
//1.建图时直接建成k+1层。
//2.多开一维记录机会信息。
//5.并查集配合dijkstra一遍，可求出对于特定的点集，每个点最近的那个同属于点集点的距离，
//6.差分约束系统
//若有 Xi-Xj<=Ck，则连一条有向边 j->i，边权为 Ck。这样求最短路可以保证 Xi-Xj<=Ck
//        然后再添加一个 0 号节点，向其他节点连一条边权为 0 的有向边，表示 Xi-X0<=0
//这样，在无负环时会得到一组非正数解（先求一组解，然后再全部加上 Δ）使用spfa可以判负环
//        最短路求得是最大值，最长路求得是最小值。(w(a,b) 表示任意一条a到达b的路径 )

template<typename T>
struct Shortest_path {
    int n;
    T inf;
    std::vector<T> dis, cnt;
    std::vector<std::vector<T>> d;
    std::vector<std::vector<std::pair<int, T>>> adj;
    std::vector<int> vis;
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>> pq;

    Shortest_path() {};

    Shortest_path(int _n, T _d = 1e9) : n(_n), inf(_d) {
        Init(_n);
    }

    void Init(int _n) {
        dis.assign(_n, inf);
        cnt.assign(_n, 0);
        vis.assign(_n, false);
        adj.assign(_n, {});
    }

    void addEdge1(int u, int v, T w) {
        adj[u].emplace_back(v, w);
    }

    void addEdge2(int u, int v, T w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void dijkstra(int s = 1) {
        fill(dis.begin(), dis.end(), inf);
        fill(vis.begin(), vis.end(), -1);

        pq.emplace(0, s);
        dis[s] = 0;
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (vis[u] >= 0) continue;
            vis[u] = s == u ? u + 1 : -vis[u];
            for (auto [v, w]: adj[u]) {
                if (dis[v] > 1ll * dis[u] + w) {
                    dis[v] = dis[u] + w;
                    vis[v] = -u - 1;
                    pq.emplace(dis[v], v);
                }
            }
        }
    }

    std::tuple<bool, std::vector<int>> path(int t) {
        std::vector<int> path;
        while (vis[t] - 1 != t) {
            path.emplace_back(t);
            t = vis[t] - 1;
            if (t < 0) return {false, {}};
        }
        path.emplace_back(t);
        std::reverse(path.begin(), path.end());
        return {{true}, path};
    }

    bool spfa(int s = 1) {
        std::queue<int> q;
        fill(dis.begin(), dis.end(), inf);
        fill(vis.begin(), vis.end(), 0);
        fill(cnt.begin(), cnt.end(), 0);
        q.emplace(s);
        dis[s] = 0;
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (auto &[v, w]: adj[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= n) return true;
                    if (!vis[v]) q.push(v), vis[v] = true;
                }
            }
        }
        return false;
    }

    bool johnson() {//全源最短路O(nmlog(m))
        d.assign(n, std::vector<T>(n, inf));
        for (int i = 1; i < n; i++) addEdge1(0, i, 0);//加虚拟边

        if (spfa(0)) return false;
        auto h = dis;//一会要用，所以保存一下
        for (int u = 1; u < n; u++) {
            for (auto &[v, w]: adj[u]) {
                w += h[u] - h[v];//新边=旧边+h[u]-h[v]
            }
        }
        for (int u = 1; u < n; u++) {
            dijkstra(u);
            for (int v = 1; v < n; v++) {
                d[u][v] = dis[v] + h[v] - h[u];//原距离等于新距离+h[v]-h[u];
            }
        }
        return true;
    }

    T K_th(int s, int t, int k) {//使用A*算法
        fill(cnt.begin(), cnt.end(), 0);
        std::vector<std::vector<std::pair<int, T>>> e(n);
        for (int i = 1; i < n; i++) {
            for (auto [v, w]: adj[i]) {
                e[v].emplace_back(i, w);
            }
        }
        dijkstra(t);
        if (s == t) k++;
        std::priority_queue<std::tuple<T, int, T>, std::vector<std::tuple<T, int, T>>, std::greater<>> q;//总长,u,已有的w
        q.emplace(dis[s], s, 0);
        while (!q.empty()) {
            auto [f, u, dd] = q.top();
            q.pop();
            cnt[u]++;//记录出队次数
            if (cnt[t] == k) return dd;
            for (auto [v, w]: e[u]) {
                if (cnt[v] < k) q.push({dis[v] + dd + w, v, dd + w});
            }
        }
        return -1;//没有第k短路
    }
};