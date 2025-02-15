//用逆元求组合数
template<typename T>
struct Comb {
    //大质数-->1999999999999999909
    T mod = 1e9+7;
    std::vector<T> fav, inv;

    Comb() {
        Init((int) 1e6);
    }

    Comb(T n) {
        Init(n);
    }

    T power(T a, T b, T p) {
        a %= p;
        T ans = 1;
        while (b) {
            if (b & 1) ans = (ans * a) % p;
            a = (a * a) % p;
            b >>= 1;
        }
        return ans;
    }

    //Cnm=n!/((n-m)!*m!)
    void Init(T n) {
        fav.resize(n + 5);
        inv.resize(n + 5);
        fav[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) {
            fav[i] = fav[i - 1] * i % mod;//求n的阶乘
        }
        inv[n] = power(fav[n], mod - 2, mod);
        for (int i = n; i > 0; i--) {
            inv[i - 1] = inv[i] * i % mod;//求n的阶乘的逆元
        }
    }

    T C(T n, T m) {
        if (n < 0 || m < 0 || n < m) return 0;
        return fav[n] * inv[m] % mod * inv[n - m] % mod;
    }

    T A(T n, T m) {
        if (n < 0 || m < 0 || n < m) return 0;
        return (fav[n] * inv[n - m]) % mod;
    }

    T lucas(T n, T m) {
        if (m == 0) return 1;
        return lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
    }

    T catalan(int n) {
        return ((C(n * 2, n) - C(n * 2, n - 1)) % mod + mod) % mod;
    }

    T catalan(int n, int m, int k) { //对于任意的i属于(n+m)时，n<=m+k,即n最多比m多k个的方案数
        if (n > m + k) return 0;
        return ((C(n + m, m) - C(n + m, m + k + 1)) % mod + mod) % mod;
    }
};