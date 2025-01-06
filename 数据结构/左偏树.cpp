//左儿子或右儿子为空的节点称为外节点
//节点的距离：该节点到最近的外界点经过的边数
//性质：
//  1.堆的性质：对于任意节点v[x]<min(v[lc[x]],v[rc[x]])(小根堆)
//  2.左偏性质：dis[lc]>=dis[rc]
//  3.任意节点的距离等于其右儿子距离+1-->dis[x]=dis[rc]+1
//  4.一个有n节点的左偏树，跟的dis<=log(n+1)-1;


template<class T>
struct LeftTree{
    int n;
    vector<T> v;
    vector<int> lc,rc,dis,fa;
    LeftTree(){};
    LeftTree(int _n){
        init(vector<T>(_n));
    }
    LeftTree(vector<T> _v) {
        init(_v);
    }
    void init(vector<T> _v){
        this->n=_v.size();
        v=_v;
        lc.resize(n);
        rc.resize(n);
        dis.resize(n);
        fa.resize(n);
        iota(fa.begin(), fa.end(),0);
        dis[0]=-1;
    }

    int find(int x){//并查集找根
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }

    int merge1(int x,int y){
        if(!x||!y) return x+y;//若第一个堆为空则返回另一个堆
        if(v[x]==v[y]?x>y:v[x]>v[y]) swap(x,y);//取小根堆做根
        rc[x]=merge1(rc[x],y);//递归合并右儿子与另一个堆

        if(dis[lc[x]]<dis[rc[x]]) swap(lc[x],rc[x]);//维护左偏性
        dis[x]=dis[rc[x]]+1;//更新dis
        return x;//返回合并后的根
    }
    int merge(int x,int y){
        int fx=find(x),fy=find(y);
        if(fx!=fy) {
            int top = merge1(fx, fy);;
            fa[fx] = fa[fy] = top;
            return top;
        }else{
            return 0;
        }
    }

    int delTop(int x){//删除所在堆的堆顶
        int fx=find(x);
        fa[lc[fx]]=fa[rc[fx]]=fa[fx]=merge1(lc[fx],rc[fx]);
        return fx;
    }
};