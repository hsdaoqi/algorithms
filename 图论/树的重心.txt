定义
	如果在树中选择某个节点并删除，这棵树将分为若干棵子树，统计子树节点数并记录最大值。取遍树上所有节点，使此最大值取到最小的节点被称为整个树的重心。
性质
	1.树的重心如果不唯一，则至多有两个，且这两个重心相邻。
	2.以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。
	3.树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。
	4.把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。
	5.在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离


std::vector<int> findCore(std::vector<std::vector<int>> &adj, int n) {
    std::vector<int> siz(n + 1), mx(n + 1), heart(n + 1), f(n + 1);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        siz[u] = 1;
        for (int v: adj[u]) {
            if (v == fa) continue;
            f[v] = u;
            dfs(v, u);
            siz[u] += siz[v];
            mx[u] = std::max(mx[u], siz[v]);
        }
        int id = u, me = mx[u];
        for (int v: adj[u]) {
            if (v == fa) continue;
            int it = heart[v], pre = std::max(mx[it], siz[u] - siz[it]), p = it;
            while (f[it] != u) {
                it = f[it];
                int now = std::max(mx[it], siz[u] - siz[it]);
                if (now < pre)pre = now, p = it;
                else break;
            }
            if (me > pre) {
                me = pre;
                id = p;
            }
        }
        heart[u] = id;
    };
    dfs(1, 0);
    return heart;
}