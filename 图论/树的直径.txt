直径的定义：不经过同一个点两次的最长链。

中心的定义：对于点 u，如果满足所有点到点 u 距离的最大值最小，则点 u 是中心。

请注意树的中心和树的重心是两个不同的概念。
1.如果一个点 u 在一条直径 D 上，D 的端点是 s 和 t，那么 u↭s 和 u↭t 中较长的一定是一条从 u 出发的最长链。
2.从任意一个点出发，能到达的最远点一定是某条直径的端点。
3.直径的端点一定都是叶子节点

int bfs(int x,std::vector<std::vector<int>> &adj){
        int n=adj.size();
        std::vector<int> dis(n,-1);
        std::queue<int> q;
        q.push(x);dis[x]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto v:adj[u]){
                if(dis[v]==-1){
                    dis[v]=dis[u]+1;
                    q.push(v);
                }
            }
        }
        int t=-1;
        for(int i=0;i<n;i++){
            if(t==-1||dis[i]>dis[t]) t=i;
        }
        return t;
    }