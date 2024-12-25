template<class T>
struct DSU {
    std::vector<int> fa, siz;
    std::vector<T> dis;

    DSU() {}

    DSU(int n) {
        init(n);
    }

    void init(int n) {
        fa.resize(n);
        dis.assign(n, 0);
        std::iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x) {
        if (fa[x] == x) return x;
        int tmp = find(fa[x]);
        dis[x] += dis[fa[x]];
        return fa[x] = tmp;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y, T v) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        dis[y] = v;
        fa[y] = x;
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }

    T dist(int x, int y) {
        if (find(x) != find(y)) return -1;
        return dis[y] - dis[x];
    }

    T dist(int x) {
        return find(x), dis[x];
    }
};