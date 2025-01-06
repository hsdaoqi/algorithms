题目描述
神犇有一个 n 个节点的图。
因为神犇是神犇，所以在 k 时间内有 m 条边会出现后消失。
神犇要求出每一时间段内这个图是否是二分图。
这么简单的问题神犇当然会做了，于是他想考考你。

输入格式
第一行三个整数 n,m,k
接下来 m行，每行四个整数 x,y,l,r，表示有一条连接 x,y的边在 l 时刻出现 r 时刻消失。

输出格式k 行，第 i 行一个字符串 Yes 或 No，表示在第 i 时间段内这个图是否是二分图。
输入输出样例
输入 #1复制
3 3 3
1 2 0 2
2 3 0 3
1 3 1 2
输出 #1复制
Yes
No
Yes

#include<bits/stdc++.h>

using i64 = long long;
std::vector<std::vector<std::pair<int, int>>> t;
std::vector<int> fa, h, ans;
std::vector<std::array<int, 3>> st;
int top;

int find(int x) {
    while (x != fa[x]) x = fa[x];
    return fa[x];
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (h[x] > h[y]) std::swap(x, y);
    st[++top] = {x, y, h[y]};
    fa[x] = y;
    h[y] += (h[x] == h[y]);
}

void insert(int u, int l, int r, int x, int y, std::pair<int, int> e) {
    if (x > r || y < l) return;
    if (x <= l && y >= r) {
        t[u].emplace_back(e);
        return;
    }
    int mid = (l + r) >> 1;
    insert(u << 1, l, mid, x, y, e);
    insert(u << 1 | 1, mid + 1, r, x, y, e);
}

void solve(int u, int l, int r, int n) {
    int flag = 0, now = top;
    for (auto [x, y]: t[u]) {
        merge(x, y + n);
        merge(y, x + n);
        if (find(x) == find(y)) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        if (l == r) {
            ans[l] = 1;
        } else {
            int mid = (l + r) >> 1;
            solve(u << 1, l, mid, n);
            solve(u << 1 | 1, mid + 1, r, n);
        }
    }

    while (top > now) {
        auto [x, y, h1] = st[top--];
        fa[x] = x;
        h[y] = h1;
    }
}

void DAOQI() {
    int n, m, k;
    std::cin >> n >> m >> k;
    fa.assign(2 * n + 1, {});
    st.assign(2 * n + 1, {});
    h.assign(2 * n + 1, {});
    ans.assign(n + 1, {});
    std::iota(fa.begin(), fa.end(), 0);
    t.assign(n << 2, {});
    for (int i = 1; i <= m; i++) {
        int x, y, l, r;
        std::cin >> x >> y >> l >> r;
        insert(1, 1, k, l + 1, r, {x, y});
    }
    solve(1, 1, k, n);
    for (int i = 1; i <= k; i++) {
        std::cout << (ans[i] ? "Yes" : "No") << "\n";
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    //std::cin >> T;
    while (T--) DAOQI();
    return 0;
}


2.
//有一张n个点m条边的无向图，第i个点只在Li到Ri这段时间出现，你需要对每个点i，判断是否存在一个时刻x使得i和1联通
#include<bits/stdc++.h>

using i64 = long long;
const int N = 2e5 + 5;
std::vector<int> L(N), R(N), fa(N), siz(N), tag(N);
std::vector<std::pair<int, int>> st(N << 2);
std::vector<std::vector<std::pair<int, int>>> tr(N << 2);
int top = 0;

void insert(int u, int l, int r, int L, int R, int x, int y) {
    if (L > r || R < l) return;
    if (L <= l && R >= r) {
        tr[u].emplace_back(x, y);
        return;
    }
    int mid = (l + r) >> 1;
    insert(u << 1, l, mid, L, R, x, y);
    insert(u << 1 | 1, mid + 1, r, L, R, x, y);
}

int find(int x) {
    if (x == fa[x]) return x;
    return find(fa[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (siz[x] > siz[y]) std::swap(x, y);
    st[++top] = {x, y};
    fa[x] = y;
    siz[y] += siz[x];
    tag[x] -= tag[y];
}

void solve(int u, int l, int r) {
    int now = top;
    for (auto [u1, v1]: tr[u]) {
        merge(u1, v1);
    }
    if (l == r) {
        tag[find(1)]++;
    } else {
        int mid = (l + r) >> 1;
        solve(u << 1, l, mid);
        solve(u << 1 | 1, mid + 1, r);
    }

    while (top > now) {
        auto [x, y] = st[top--];
        fa[x] = x;
        siz[y] -= siz[x];
        tag[x] += tag[y];
    }
}

void DAOQI() {
    int n, m, k = 2e5 + 5;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        std::cin >> L[i] >> R[i];
        fa[i] = i, siz[i] = 1;
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        int l = std::max(L[x], L[y]), r = std::min(R[x], R[y]);
        if (l <= r) {
            insert(1, 1, k, l, r, x, y);
        }
    }
    solve(1, 1, k);
    for (int i = 1; i <= n; i++) {
        if (tag[i]) {
            std::cout << i << " ";
        }
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    //std::cin >> T;
    while (T--) DAOQI();
    return 0;
}