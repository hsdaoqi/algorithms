/**
 * 矩阵（Matrix）
**/
using i64 = long long;

template<class T, int R, int C>
struct Matrix {
    std::array<T, R * C> A;
    int n{}, m{};

    Matrix(int _r = R, int _c = C) {
        init(_r, _c);
    }

    void init(int _r, int _c) {
        n = _r, m = _c;
        A.fill(0);
    }

    int id(int i, int j) const {
        return i * m + j;
    }

    T at(int i, int j) const {
        assert(id(i, j) >= 0 && id(i, j) < n * m);
        return A[id(i, j)];
    }

    T &operator[](int i) {
        assert(i >= 0 && i < n * m);
        return A[i];
    }

    Matrix<T, R, C> &operator=(const std::array<T, R * C> &a) {
        A = a;
        return *this;
    }

    template<int N, int M>
    Matrix<T, R, M> operator*(const Matrix<T, N, M> &rhs) {
        assert(C == N);
        Matrix<T, R, M> c(n, rhs.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < rhs.m; j++) {
                for (int k = 0; k < m; k++) {
                    c[c.id(i, j)] = c.at(i, j) + A[id(i, k)] * rhs.at(k, j);
                }
            }
        }
        return c;
    }

    Matrix<T, R, C> operator*(const T &a) {
        Matrix<T, R, C> c(n, m);
        for (int i = 0; i < n * m; i++) {
            c[i] = a * A[i];
        }
        return c;
    }

    friend Matrix<T, R, C> operator*(const T &a, const Matrix<T, R, C> &lhs) {
        Matrix<T, R, C> c(lhs.n, lhs.m);
        for (int i = 0; i < lhs.n * lhs.m; i++) {
            c[i] = a * lhs[i];
        }
        return c;
    }

    Matrix<T, R, C> operator+(const Matrix<T, R, C> &rhs) {
        Matrix<T, R, C> c(n, m);
        for (int i = 0; i < n * m; i++) {
            c[i] = A[i] + rhs.A[i];
        }
        return c;
    }

    Matrix<T, R, C> operator-(const Matrix<T, R, C> &rhs) {
        Matrix<T, R, C> c(n, m);
        for (int i = 0; i < n * m; i++) {
            c[i] = A[i] - rhs.A[i];
        }
        return c;
    }

    friend bool operator==(const Matrix<T, R, C> &lhs, const Matrix<T, R, C> &rhs) {
        if (lhs.n != rhs.n && lhs.m != rhs.m) return false;
        for (int i = 0; i < lhs.n * lhs.m; i++) {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const Matrix<T, R, C> &lhs, const Matrix<T, R, C> &rhs) {
        if (lhs.n != rhs.n && lhs.m != rhs.m) return true;
        for (int i = 0; i < lhs.n * lhs.m; i++) {
            if (lhs[i] != rhs[i]) return true;
        }
        return false;
    }

    friend constexpr std::istream &operator>>(std::istream &is, Matrix<T, R, C> &rhs) {
        for (int i = 0; i < rhs.n * rhs.m; i++) {
            is >> rhs[i];
        }
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, Matrix<T, R, C> &rhs) {
        for (int i = 0; i < rhs.n; i++) {
            for (int j = 0; j < rhs.m; j++) {
                os << rhs.at(i, j) << " ";
            }
            os << " \n"[i < rhs.n - 1];
        }
        return os;
    }
};

template<class T, int R>
Matrix<T, R, R> unit(int N) {//单位矩阵
    Matrix<T, R, R> E(N, N);
    for (int i = 0; i < N; i++) {
        E[E.id(i, i)] = 1;
    }
    return E;
}

template<class T, int R, int C>
Matrix<T, C, R> transpose(const Matrix<T, R, C> &A) {//矩阵转置
    Matrix<T, C, R> B(A.m, A.n);
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < A.m; j++) {
            B[B.id(j, i)] = A.at(i, j);
        }
    }
    return B;
}

template<class T, int R>
T det(const Matrix<T, R, R> &A) {//方阵的行列式
    int n = A.n, m = A.m;
    assert(n == m);
    Matrix<long double, R, R> B(n, m);
    for (int i = 0; i < n * m; i++) B[i] += A.at(0, i);
    for (int c = 0; c < m; c++) {
        int ok = false, r = c;
        for (r = c; r < n; r++) {
            if (B.at(r, c) != 0) {
                ok = true;
                for (int j = 0; j < n; j++) {
                    std::swap(B[B.id(c, j)], B[B.id(r, j)]);
                }
                break;
            }
        }
        if (!ok) return 0;
        r++;
        for (; r < n; r++) {
            if (B.at(r, c) == 0) continue;
            long double t = B.at(r, c) / B.at(c, c);
            for (int j = c; j < n; j++) {
                B[B.id(r, j)] -= B[B.id(c, j)] * t;
            }
        }
    }
    T ans = 1;
    for (int i = 0; i < n; i++) {
        ans *= B.at(i, i);
    }
    return ans;
}

template<class T, int R, int C>
Matrix<T, R, C> adjont(const Matrix<T, R, C> &A) {//伴随矩阵
    int n = A.n, m = A.m;
    assert(n == m);
    Matrix<T, R, C> B(n, n);
    Matrix<T, R - 1, R - 1> tmp(n - 1, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int idx = 0;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (x == i || y == j) continue;
                    tmp[idx++] = A.at(x, y);
                }
            }
            B[B.id(j, i)] = ((i + j) % 2 ? -1 : 1) * det(tmp);
        }
    }
    return B;
}


template<class T, int R, int C>
Matrix<T, R, C> power(Matrix<T, R, C> a, i64 b) {
    auto ans = unit<T, R>(a.n);
    assert(a.n == a.m);
    for (; b; b >>= 1, a = a * a) {
        if (b & 1) ans = ans * a;
    }
    return ans;
}