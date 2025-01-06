template<class T>
struct grid {
    int n;
    std::vector<std::vector<T>> c;

    grid(int n_ = 100) : n(n_) {
        c.resize(n + 1, std::vector<T>(n + 1, {}));
    }
};

template<class T>
grid<T> operator*(grid<T> &x, grid<T> &y) {
    int n = x.n;
    grid<T> tmp(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                tmp.c[i][j] = (tmp.c[i][j] + x.c[i][k] * y.c[k][j]) % mod;
            }
        }
    }
    return tmp;
}

template<class T>
grid<T> power(grid<T> a, T b) {
    grid<T> ans(a.n);
    for (int i = 1; i <= ans.n; i++) ans.c[i][i] = 1;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}