template<class T>
struct Tree {
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
    T inf = std::numeric_limits<T>::max();

    struct node {
        int son[2];//左右儿子
        int parent;//父亲
        T val;//节点权值
        int cnt;//权值出现次数
        int siz;//子树大小
        void init(int parent_, T val_) {
            parent = parent_, val = val_;
            cnt = siz = 1;
        }
    };

    std::vector<node> t;
    int root;//根节点编号，节点个数

    Tree() {
        Init();
    }

    int newnode() {
        t.emplace_back();
        return t.size() - 1;
    }

    void Init() {
        t.assign(1, {});
        root = 0;
        insert(1e9);
        insert(-1e9);
    }

    void pushup(int x) {//x下标
        t[x].siz = t[ls(x)].siz + t[rs(x)].siz + t[x].cnt;
    }

    void rotat(int x) {//左旋右旋
        int y = t[x].parent, z = t[y].parent;//父节点，爷爷节点
        int k = t[y].son[1] == x;//判断x是y的左孩子还是右孩子
        t[z].son[t[z].son[1] == y] = x;//先判断y是左孩子还是右孩子，再x将原来y的位置顶替
        t[x].parent = z;
        t[y].son[k] = t[x].son[k ^ 1];//若x是y的左孩子则进行右旋，将x的右孩子转移到y的左孩子上，反之亦然
        t[t[x].son[k ^ 1]].parent = y;
        t[x].son[k ^ 1] = y;
        t[y].parent = x;
        pushup(y);
        pushup(x);
    }

    void splay(int x, int k) {
        while (t[x].parent != k) {
            int y = t[x].parent, z = t[y].parent;
            if (z != k)//折转底，直转中
                (ls(y) == x) ^ (ls(z) == y) ? rotat(x) : rotat(y);

            rotat(x);
        }
        if (!k) root = x;
    }

    void insert(T v) {//插入数值v
        int x = root, p = 0;
        while (x && t[x].val != v) {
            p = x, x = t[x].son[v > t[x].val];
        }

        if (x) t[x].cnt++;
        else {
            x = newnode();
            t[p].son[v > t[p].val] = x;
            t[x].init(p, v);
        }
        splay(x, 0);
    }

    void find(T v) {//找到数值v并转到根
        int x = root;
        while (t[x].son[v > t[x].val] && v != t[x].val) x = t[x].son[v > t[x].val];
        splay(x, 0);
    }

    int get_pre(T v) {//数值v前驱的编号
        find(v);
        int x = root;
        if (t[x].val < v) return x;
        x = ls(x);
        while (rs(x)) x = rs(x);

        splay(x, 0);
        return x;
    }

    int get_suc(T v) {//数值v后继的节点
        find(v);
        int x = root;
        if (t[x].val > v) return x;
        x = rs(x);
        while (ls(x)) x = ls(x);

        splay(x, 0);
        return x;
    }

    void del(T v) {//数值v删除
        int pre = get_pre(v);
        int suc = get_suc(v);
        splay(pre, 0);
        splay(suc, pre);
        int del = t[suc].son[0];
        if (t[del].cnt > 1) {
            t[del].cnt--, splay(del, 0);
        } else {
            t[suc].son[0] = 0, splay(suc, 0);
        }
    }

    int get_rank(T v) {//数值排名
        insert(v);
        int res = t[t[root].son[0]].siz;
        del(v);
        return res;
    }

    T get_val_by_rank(int k) {//数值
        int x = root;
        while (1) {
            int y = ls(x);
            if (t[y].siz + t[x].cnt < k) {
                k -= t[y].siz + t[x].cnt;
                x = rs(x);
            } else if (t[y].siz >= k) {
                x = y;
            } else break;
        }
        splay(x, 0);
        return t[x].val;
    }
};