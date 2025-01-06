#include <bits/stdc++.h>
using namespace std;

//求最近公共祖先：倍增算法
const int N = 5e5+10;
int n,m,s,a,b;
vector<int> e[N];
int dep[N],f[N][20];//dep[i]:编号为i的节点的深度，f[u][i]u节点往上跳2^i层节点是谁

void dfs(int u,int father){
    dep[u]=dep[father]+1;
    f[u][0]=father;//往上跳2^i层的节点
    for(int i=1;i<=19;i++){//小于多少由总节点数决定
        f[u][i]=f[f[u][i-1]][i-1];//递推式
    }
    for(int v:e[u]){
        if(v!=father) dfs(v,u);
    }
}

int lca(int u,int v){//u节点和v节点的公共祖先
    if(dep[u]<dep[v]) swap(u,v);//让u的深度更深，方便计算
    //先跳到同一层
    for(int i=19;i>=0;i--){
        if(dep[f[u][i]]>=dep[v])//将两层之差转化为二进制看看有几个1进行跳跃
            u=f[u][i];
    }
    if(u==v)return u;
    //两个点同时跳到上一层直到相遇
    for(int i=19;i>=0;i--){
        if(f[u][i]!=f[v][i])
            u=f[u][i],v=f[v][i];
    }
    return f[u][0];
}



//Tarjan算法
const int N=1e5+5;
vector<int> e[N];
vector<pair<int,int>> query[N];
int fa[N],vis[N],ans[N];
//e[u]存边，query[u]存查寻，first=v,second=i,u和v的最近公共祖先，i为第几个查询，
//fa[u]存父节点,vis[u]标记，ans[i]存查寻结果
int find(int u){
    if(u==fa[u]) return u;
    return fa[u]=find(fa[u]);
}
void tarjan(int u){
    vis[u]=true;
    for(auto v:e[u]){
        if(!vis[v]){
            tarjan(v);
            fa[v]=u;
        }
    }
    //离u时，枚举LCA
    for(auto q:query[u]){
        int v=q.first,i=q.second;
        if(vis[v]) ans[i]=find(v);
    }
}

int main(){
    int n,m;cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        query[u].emplace_back(v,i);
        query[v].emplace_back(u,i);
    }
    for(int i=1;i<=n;i++) fa[i]=i;
}



// 树链剖分
//重儿子：父节点的所有儿子中子树节点数目最多的节点
//轻儿子：重儿子以外的节点
//重边：父节点和重儿子连成的边
//轻边：父节点和轻儿子连成的边
//重链：多条重边连接而成的路径
const int N=5e5+5;
vector<int> e[N],fa(N),dep(N),son(N),sz(N),top(N);
//fa[u]:存u的父节点，dep[u]：u的深度，son[u]:存u的重儿子，sz[u],存以u为根的子树的节点数，top[u]:存u所在重链的顶点

void dfs1(int u,int father){//搞fa,dep,son
    fa[u]=father,dep[u]=dep[father]+1,sz[u]=1;
    for(int v:e[u]){
        if(v==father) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]) son[u]=v;
    }
}

void dfs2(int u,int t){//搞top
    top[u]=t;//记录链头
    if(!son[u]) return;//无重儿子，返回
    dfs2(son[u],t);//搜重儿子
    for(int v:e[u]){
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);//搜轻儿子,轻儿子一定是某条重链的头节点
    }
}

int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);//方便写代码
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}
