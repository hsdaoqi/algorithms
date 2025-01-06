给你一棵有根的树，根位于顶点 1 。每个顶点都涂有某种颜色。

如果在顶点 v 的子树中，没有其他颜色比颜色 c 出现的次数更多，那么我们就称颜色 c 在顶点 v 的子树中占主导地位。因此，在某个顶点的子树中，可能会有两种或两种以上的颜色占主导地位。

顶点 v 的子树是顶点 v 和其他所有包含顶点 v 的顶点。

针对每个顶点 v 求顶点 v 的子树中所有支配色的总和。

#include<bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> col(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> col[i];
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int cur = 0;
    std::vector<int> ls(n * 50), rs(n * 50), cnt(n * 50), root(n + 1);
    std::vector<i64> sum(n * 50);
    auto pushup = [&](int u) {
        if (cnt[ls[u]] == cnt[rs[u]]) {
            cnt[u] = cnt[ls[u]];
            sum[u] = sum[ls[u]] + sum[rs[u]];
        } else {
            int t = ls[u];
            if (cnt[ls[u]] < cnt[rs[u]]) t = rs[u];
            cnt[u] = cnt[t];
            sum[u] = sum[t];
        }
    };

    std::function<void(int &, int, int, int)> apply = [&](int &u, int l, int r, int p) {
        if (!u) u = ++cur;
        if (l == r) {
            cnt[u] += 1;
            sum[u] = p;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) apply(ls[u], l, mid, p);
        else apply(rs[u], mid + 1, r, p);
        pushup(u);
    };

    for (int i = 1; i <= n; i++) {
        apply(root[i], 1, n, col[i]);
    }

    std::function<int(int, int, int, int)> merge = [&](int u, int v, int l, int r) -> int {
        if (!u || !v) return u + v;
        if (l == r) {
            cnt[u] += cnt[v];
            return u;
        }
        int mid = (l + r) >> 1;
        ls[u] = merge(ls[u], ls[v], l, mid);
        rs[u] = merge(rs[u], rs[v], mid + 1, r);
        pushup(u);
        return u;
    };

    std::vector<i64> ans(n + 1);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        for (int v: adj[u]) {
            if (v == fa) continue;
            dfs(v, u);
            root[u] = merge(root[u], root[v], 1, n);
        }
        ans[u] = sum[root[u]];
    };

    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << " ";
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