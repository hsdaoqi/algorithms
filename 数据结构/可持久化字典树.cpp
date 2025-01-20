~~~ c++
template<class T>
struct PerTrie {
    int cur = 0;
    std::vector<std::array<int, 2>> t;
    std::vector<int> ver, bor;
    T inf = std::numeric_limits<T>::max();

    PerTrie() {
        init();
    }

    void init() {
        t.assign(1, {});
        ver.assign(1, {});
        bor.assign(1, {});
    }

    void add(T x, T y = 0) {
        int p = ++cur;
        ver.emplace_back(p);
        for (int i = std::__lg(inf); i >= 0; i--) {
            int q = x >> i & 1;
            while (p >= t.size()) t.emplace_back();
            t[p][!q] = t[y][!q];
            t[p][q] = ++cur;
            p = t[p][q], y = t[y][q];
            while (p >= bor.size()) bor.emplace_back();
            bor[p] = bor[y] + 1;
        }
    }

    T query(int l, int r, T x) {
        T ans = 0;
        for (int i = std::__lg(inf); i >= 0; i--) {
            int q = x >> i & 1;
            if (bor[t[r][!q]] > bor[t[l][!q]]) {
                r = t[r][!q], l = t[l][!q], ans += 1ll << i;
            } else {
                r = t[r][q], l = t[l][q];
            }
        }
        return ans;
    }

    int version(int p) {
        return ver[p];
    }

    int size() {
        return ver.size();
    }
};
~~~

