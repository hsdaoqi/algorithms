题目描述
给出一个可重集 a（编号为 1），它支持以下操作：
0 p x y：将可重集 p 中大于等于 x 且小于等于 y 的值移动到一个新的可重集中（新可重集编号为从 2 开始的正整数，是上一次产生的新可重集的编号+1）。
1 p t：将可重集 t 中的数放入可重集 p，且清空可重集 t（数据保证在此后的操作中不会出现可重集 t）。
2 p x q：在 p 这个可重集中加入 x 个数字 q。
3 p x y：查询可重集 p 中大于等于 x 且小于等于 y 的值的个数。
4 p k：查询在 p 这个可重集中第 k 小的数，不存在时输出 -1。

输入格式
第一行两个整数n,m表示可重集中的数在 1∼n 的范围内，有 m 个操作。
接下来一行 n 个整数，表示 1∼n 这些数在 a 中出现的次数 (ai≤m)
接下来的 m 行每行若干个整数，第一个数为操作的编号opt（0≤opt≤4），以题目描述为准。

#include<bits/stdc++.h>

using i64 = long long;

const int N = 2e5 + 5;
int ls[N * 30], rs[N * 30], root[N];
int cur = 0;
i64 sum[N * 30];

void apply(int &u, int l, int r, int p, int k) {
    if (!u) u = ++cur;
    if (l == r) {
        sum[u] += k;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) apply(ls[u], l, mid, p, k);
    else apply(rs[u], mid + 1, r, p, k);
    sum[u] = sum[ls[u]] + sum[rs[u]];
}

i64 query(int u, int l, int r, int x, int y) {
    if (x > r || y < l) return 0;
    if (x <= l && y >= r) return sum[u];
    int mid = (l + r) >> 1;
    return query(ls[u], l, mid, x, y) + query(rs[u], mid + 1, r, x, y);
}

void split(int x, int &y, i64 k) {
    if (x == 0) return;
    y = ++cur;
    i64 s = sum[ls[x]];
    if (k <= s) {
        split(ls[x], ls[y], k);
        std::swap(rs[x], rs[y]);
    } else {
        split(rs[x], rs[y], k - s);
    }
    sum[y] = sum[x] - k, sum[x] = k;
}

int merge(int &x, int y, int l, int r) {
    if (!x || !y) { return x + y; }
    if (l == r) {
        sum[x] += sum[y];
        return x;
    }
    int mid = (l + r) >> 1;
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    sum[x] = sum[ls[x]] + sum[rs[x]];
    return x;
}

int kth(int u, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (k <= sum[ls[u]]) return kth(ls[u], l, mid, k);
    else return kth(rs[u], mid + 1, r, k - sum[ls[u]]);
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        apply(root[1], 1, n, i, x);
    }

    int cnt = 1;
    for (int i = 1; i <= m; i++) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int p, x, y;
            std::cin >> p >> x >> y;
            i64 k1 = query(root[p], 1, n, 1, y), k2 = query(root[p], 1, n, x, y);
            int tmp = 0;
            split(root[p], root[++cnt], k1 - k2);
            split(root[cnt], tmp, k2);
            root[p] = merge(root[p], tmp, 1, n);
        } else if (op == 1) {
            int x, y;
            std::cin >> x >> y;
            root[x] = merge(root[x], root[y], 1, n);
        } else if (op == 2) {
            int p, x, y;
            std::cin >> p >> x >> y;
            apply(root[p], 1, n, y, x);
        } else if (op == 3) {
            int p, x, y;
            std::cin >> p >> x >> y;
            std::cout << query(root[p], 1, n, x, y) << "\n";
        } else {
            int p, x;
            std::cin >> p >> x;
            if (sum[root[p]] < x) std::cout << -1 << "\n";
            else std::cout << kth(root[p], 1, n, x) << "\n";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    //std::cin >> T;
    while (T--) solve();
    return 0;
}
