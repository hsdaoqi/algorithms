/**   可撤销并查集（DSU With Rollback）
**/
struct DSU {
    int n;
    std::vector<int> siz, f;
    std::vector<std::array<int, 2>> his;

    DSU(int _n = 1) {
        init(_n);
    }

    void init(int _n) {
        this->n = _n;
        siz.assign(n, 1);
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int time() {
        return his.size();
    }

    void revert(int tm) {
        while (his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }

    int size(int p) {
        return siz[find(p)];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};