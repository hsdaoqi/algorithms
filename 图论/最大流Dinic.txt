template<class T>
struct MaxFlow{
    struct _Edge{
        int to;
        T cap;
        _Edge(int _to,T _cap):to(_to),cap(_cap){};
    };

    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> h;
    std::vector<int> cur,d;

    MaxFlow(){};
    MaxFlow(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        e.clear();
        h.assign(n,{});
        cur.resize(n);
        d.resize(n);
    }
    void addEdge(int u,int v,T c){
        h[u].push_back(e.size());
        e.emplace_back(v,c);
        h[v].push_back(e.size());
        e.emplace_back(u,0);
    }

    bool bfs(int s,int t){
        d.assign(n,0);
        std::queue<int> q;
        d[s]=1;q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i:h[u]){
                auto [v,c]=e[i];
                if(c>0&&d[v]==0){
                    d[v]=d[u]+1;
                    if(v==t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u,int t,T f){
        if(u==t) return f;
        T sum=f;
        for(int &i=cur[u];i<(int)h[u].size();i++){
            int j=h[u][i];
            auto [v,c]=e[j];
            if(c>0&&d[v] == d[u]+1){
                T a = dfs(v,t,std::min(sum,c));
                e[j].cap-=a;
                e[j^1].cap+=a;
                sum-=a;
                if(sum==0) return f;
            }
        }
        if(sum==f) d[u]=0;
        return f-sum;
    }

    T Dinic(int s,int t){
        T ans=0;
        while(bfs(s,t)){
            cur.assign(n,0);
            ans+=dfs(s,t,std::numeric_limits<T>::max());
        }
        return ans;
    }

    std::vector<bool> minCut(){
        std::vector<bool> c(n);
        for(int i=1;i<n;i++){
            c[i]=(d[i]!=0);
        }
        return c;
    }

    struct Edge {
        int from,to;
        T cap,flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};