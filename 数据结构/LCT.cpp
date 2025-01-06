struct LCT {
#define fa(x) t[x].fa
#define lc(x) t[x].ch[0]
#define rc(x) t[x].ch[1]
#define notroot(x) lc(fa(x))==x||rc(fa(x))==x
    struct node { //splay的信息
        int ch[2], fa, v, sum;
        int tag; //翻转懒标记
    };

    std::vector<node> t;

    LCT() {
        init(1);
    }

    LCT(int n) {
        init(n);
    }

    void init(int n = 1) {
        t.assign(n, {});
    }

    void pushup(int x) { //上传
        t[x].sum = t[lc(x)].sum ^ t[x].v ^ t[rc(x)].sum;
    }

    void pushdown(int x) { //下传
        if (t[x].tag) {
            std::swap(lc(x), rc(x));
            t[lc(x)].tag ^= 1;
            t[rc(x)].tag ^= 1;
            t[x].tag = 0;
        }
    }

    void pushall(int x) { //递归下传
        if (notroot(x)) pushall(fa(x));
        pushdown(x);
    }

    void rotate(int x) { //旋转x
        int y = fa(x), z = fa(y), k = rc(y) == x; //y的右儿是x
        if (notroot(y)) t[z].ch[rc(z) == y] = x;
        fa(x) = z; //z的儿是x,x的父是z
        t[y].ch[k] = t[x].ch[k ^ 1];
        fa(t[x].ch[k ^ 1]) = y; //y的儿是x的异儿,x的异儿的父是y
        t[x].ch[k ^ 1] = y;
        fa(y) = x; //x的异儿是y,y的父是x
        pushup(y);
        pushup(x); //自底向上pushup
    }

    void splay(int x) { //x伸展到根
        pushall(x); //递归下传
        while (notroot(x)) { //折线转xx,直线转yx
            int y = fa(x), z = fa(y);
            if (notroot(y)) (rc(y) == x) ^ (rc(z) == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }

    void access(int x) { //打通x到树根的路
        for (int y = 0; x;) {
            splay(x); //x转到当前splay的根
            rc(x) = y;  //x的右儿指向下面splay的根
            pushup(x); //更新x的sum
            y = x, x = fa(x); //存x,x爬到上面的splay
        }
    }

    void makeroot(int x) { //换根
        access(x); //通路
        splay(x);  //伸展
        t[x].tag ^= 1; //翻转懒标记
    }

    void split(int x, int y) { //分离x到y的路径
        makeroot(x); //x换根
        access(y); //y通路
        splay(y);  //y伸展
    }

    void output(int x, int y) { //输出
        split(x, y); //分离
        printf("%d\n", t[y].sum);
    }

    int findroot(int x) { //找根
        access(x);
        splay(x);
        while (lc(x)) pushdown(x), x = lc(x);
        splay(x); //防止卡链
        return x;
    }

    void link(int x, int y) { //连边
        makeroot(x);
        if (findroot(y) != x) fa(x) = y;
    }

    void cut(int x, int y) { //断边
        makeroot(x);
        if (findroot(y) == x && fa(y) == x && !lc(y))
            fa(y) = 0, pushup(x);
    }

    void change(int x, int y) { //修改
        splay(x);
        t[x].v = y;
        pushup(x);
    }
};