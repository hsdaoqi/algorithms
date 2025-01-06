//二分图最大匹配匈牙利算法
int Hgr(vector<vector<int>> &adj){
    vector<int> vis(adj.size()),match(adj.size());
    int cnt=0;
    function<bool(int)> dfs=[&](int u)->bool{
        for(int v:adj[u]){
            if(vis[v]) continue;
            vis[v]=1;
            if(!match[v]||dfs(match[v])){
                match[v]=u;
                return true;
            }
        }
        return false;
    };
    for(int i=1;i<adj.size();i++){
        fill(vis.begin(),vis.end(),0);
        if(dfs(i)) cnt++;
    }
    return cnt;
}