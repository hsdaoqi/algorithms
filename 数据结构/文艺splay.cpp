//文艺平衡树Splay
template<class T>
struct Tree {
#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]
    T inf = std::numeric_limits<T>::max();

    struct node {
        int son[2];//左右儿子
        int parent;//父亲
        T val;//节点权值
        int siz;//子树大小
        int tag;//懒标记
        void init(int parent_, T val_) {
            parent = parent_, val = val_;
            siz = 1;
        }
    };

    std::vector<node> tr;
    int root;//根节点编号

    Tree() {
        Init();
    }

    int newnode() {
        tr.emplace_back();
        return tr.size() - 1;
    }

    void Init() {
        tr.assign(1, {});
        root = 0;
        insert(-inf);
        insert(inf);
    }

    void pushup(int x) {//x下标
        tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz + 1;
    }

    void pushdown(int x) {//下传
        if (tr[x].tag) {
            std::swap(ls(x), rs(x));
            tr[ls(x)].tag ^= 1;
            tr[rs(x)].tag ^= 1;
            tr[x].tag = 0;
        }
    }

    void rotat(int x) {//左旋右旋
        int y = tr[x].parent, z = tr[y].parent;//父节点，爷爷节点
        int k = tr[y].son[1] == x;//判断x是y的左孩子还是右孩子
        tr[z].son[tr[z].son[1] == y] = x;//先判断y是左孩子还是右孩子，再x将原来y的位置顶替
        tr[x].parent = z;
        tr[y].son[k] = tr[x].son[k ^ 1];//若x是y的左孩子则进行右旋，将x的右孩子转移到y的左孩子上，反之亦然
        tr[tr[x].son[k ^ 1]].parent = y;
        tr[x].son[k ^ 1] = y;
        tr[y].parent = x;
        pushup(y);
        pushup(x);
    }

    void splay(int x, int k) {
        while (tr[x].parent != k) {
            int y = tr[x].parent, z = tr[y].parent;
            if (z != k)//折转底，直转中
                (ls(y) == x) ^ (ls(z) == y) ? rotat(x) : rotat(y);

            rotat(x);
        }
        if (!k) root = x;
    }

    void insert(int v) {//插入数值v
        int x = root, p = 0;
        while (x) {
            p = x, x = tr[x].son[v > tr[x].val];
        }
        x = newnode();
        tr[p].son[v > tr[p].val] = x;
        tr[x].init(p, v);
        splay(x, 0);
    }

    int get_k(int k) {//返回现数组第k的数节点编号
        int x = root;
        while (true) {
            pushdown(x);
            int y = ls(x);
            if (tr[y].siz + 1 < k) k -= tr[y].siz + 1, x = rs(x);
            else if (tr[y].siz >= k) x = y;
            else return x;
        }
    }

    void output(int x) {//中序遍历输出
        pushdown(x);
        if (ls(x)) output(ls(x));
        if (tr[x].val > -inf && tr[x].val < inf) std::cout << tr[x].val << " ";
        if (rs(x)) output(rs(x));
    }
};