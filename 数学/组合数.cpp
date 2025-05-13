/*
 * 组合数(Comb)
 * */
template<typename T>
struct Comb {
    //大质数-->1999999999999999909
    T mod = 1e9 + 7;
    int n = 0;
    std::vector<T> _fac, _inv, _invfac;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    explicit Comb(int n) : Comb() {
        init(n);
    }

    T power(T a, i64 b) {
        T ans = 1;
        for (; b; b >>= 1, a = a * a % mod) {
            if (b & 1) ans = ans * a % mod;
        }
        return ans;
    }

    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _inv.resize(m + 1);
        _invfac.resize(m + 1);
        _fac[0] = _inv[0] = _invfac[0] = 1;
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i % mod;
        }
        _invfac[m] = power(_fac[m], mod - 2);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i % mod;
            _inv[i] = _invfac[i] * _fac[i - 1] % mod;
        }
        n = m;
    }

    T sub(T a, T b) {
        return ((a - b) % mod + mod) % mod;
    }

    T fac(int m) {
        if (m > n) init(m);
        return _fac[m];
    }

    T invfac(int m) {
        if (m > n) init(m);
        return _invfac[m];
    }

    T inv(int m) {
        if (m > n) init(m);
        return _inv[m];
    }

    T binom(int _n, int m) {
        if (_n < 0 || m < 0 || _n < m) return 0;
        return fac(_n) * invfac(m) % mod * invfac(_n - m) % mod;
    }

    T perm(int _n, int m) {
        if (_n < 0 || m < 0 || _n < m) return 0;
        return fac(_n) * invfac(_n - m) % mod;
    }

    T lucas(i64 _n, i64 m) {
        if (m == 0) return 1;
        return lucas(_n / mod, m / mod) * binom(_n % mod, m % mod) % mod;
    }

    T catalan(int _n) {
        return sub(binom(_n * 2, _n), binom(_n * 2, _n - 1));
    }

    T catalan(int _n, int m, int k) { //对于任意的i属于(_n+m)时，_n<=m+k,即n最多比m多k个的方案数
        if (_n > m + k) return 0;
        return sub(binom(_n + m, m), binom(_n + m, m + k + 1));
    }
};