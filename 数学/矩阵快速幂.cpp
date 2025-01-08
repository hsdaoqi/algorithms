/**
 * 矩阵（Matrix）
**/
using i64 = long long;
constexpr int N = 2;
constexpr int mod = 1e9 + 7;
using Matrix = std::array<i64, N * N>;

int id(int i, int j) {
    return i * N + j;
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c{};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[id(i, j)] = (c[id(i, j)] + a[id(i, k)] * b[id(k, j)]) % mod;
            }
        }
    }
    return c;
}

Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c{};
    for (int i = 0; i < N * N; i++) {
        c[i] = (a[i] + b[i]) % mod;
    }
    return c;
}

Matrix power(Matrix a, i64 b) {
    Matrix ans{};
    for (int i = 0; i < N; i++) ans[id(i, i)] = 1;
    for (; b; b >>= 1, a = a * a) {
        if (b & 1) ans = ans * a;
    }
    return ans;
}

Matrix init(Matrix &mat, int x = 0) {
    if (x == 0) {
        mat.fill(0);
    } else {
        for (int i = 0; i < N; i++) mat[id(i, i)] = x;
    }
    return mat;
}