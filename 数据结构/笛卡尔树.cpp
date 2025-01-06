//笛卡尔树
template<class T, typename Compare=std::less<T>>
struct CartesianTree {
    T inf = std::numeric_limits<T>::max();

    struct Node {
        int idx;
        T val;
        int par;
        std::array<T, 2> son;

        Node(int idx = 0, T val = 0, int par = 0) : idx(idx), val(val), par(par), son{} {}
    };

    std::vector<Node> t;

    CartesianTree() {
        init();
    }

    void init(Compare comp = Compare()) {
        t.assign(1, {0, 0, 0});
        t[0].son.fill(0);
        if (comp(-inf, inf)) t[0].val = -inf;
        else t[0].val = inf;
    }

    void add(int idx, T val, int par = 0) {
        t.emplace_back(idx, val, par);
    }

    int work(Compare comp = Compare()) {
        for (int i = 1; i < t.size(); i++) {
            int k = i - 1;
            while (comp(t[i].val, t[k].val)) k = t[k].par;
            t[i].son[0] = t[k].son[1];
            t[k].son[1] = i;
            t[i].par = k;
            t[t[i].son[0]].par = i;
        }
        return t[0].son[1];
    }

    int ls(int p) { return t[p].son[0]; }

    int rs(int p) { return t[p].son[1]; }

    int par(int p) { return t[p].par; }
};