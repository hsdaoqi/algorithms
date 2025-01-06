//二分图最大权完美匹配KM
//求解最小权：边权取反

template<class T>
struct KM {
    int n, inf;
    std::vector<T> c, la, lb;//左右点顶标
    std::vector<std::vector<T>> w;//边权
    std::vector<int> pre, va, vb, match;//访问标记，是否在交错树中,右部点匹配的左部点
    KM() {};

    KM(int _n) : n(_n) {
        init(_n);
    }

    void init(int _n) {
        inf = std::numeric_limits<T>::max() / 2;
        c.resize(n);
        match.resize(n);
        la.assign(n, -inf);
        lb.resize(n);
        w.assign(n, std::vector<T>(n, -inf));
        pre.resize(n);
        va.resize(n);
        vb.resize(n);
    }

    void addEdge(int u, int v, T ww) {
        w[u][v] = std::max(w[u][v], ww);
    }

    void bfs(int x) {
        int a, y = 0, ney = 0;
        fill(pre.begin(), pre.end(), 0);
        fill(c.begin(), c.end(), inf);
        match[y] = x;

        do {
            a = match[y], vb[y] = true;
            T delta = inf;
            for (int b = 1; b < n; b++) {
                if (!vb[b]) {
                    if (c[b] > la[a] + lb[b] - w[a][b])
                        c[b] = la[a] + lb[b] - w[a][b], pre[b] = y;
                    if (c[b] < delta) //Δ还是取最小的
                        delta = c[b], ney = b;
                }
            }

            for (int b = 0; b < n; b++) {
                if (vb[b]) la[match[b]] -= delta, lb[b] += delta;
                else c[b] -= delta;
            }
            y = ney;
        } while (match[y]);

        while (y) {
            match[y] = match[pre[y]];
            y = pre[y];
        }
    }

    T work() {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                la[i] = std::max(la[i], w[i][j]);
            }
        }
        for (int i = 1; i < n; i++) {
            fill(vb.begin(), vb.end(), 0);
            bfs(i);
        }
        T res = 0;
        for (int i = 1; i < n; i++) {
            res += w[match[i]][i];
        }
        return res;
    }
};