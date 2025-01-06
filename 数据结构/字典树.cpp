
struct Trie {
    struct node {
        std::array<int, 26> son;
        int cnt = 0;

        node() : son{} {}
    };

    std::vector<node> t;

    Trie() {
        init();
    }

    void init() {
        t.assign(1, node());
    }

    int newnode() {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(const std::string &val) {
        int p = 0;
        for (char c: val) {
            int ne = c - 'a';
            if (t[p].son[ne] == 0) {
                t[p].son[ne] = newnode();
            }
            p = t[p].son[ne];
        }
        t[p].cnt++;
    }

    int query(const std::string &val) {
        int p = 0;
        for (char c: val) {
            int ne = c - 'a';
            if (t[p].son[ne] == 0) {
                return 0;
            }
            p = t[p].son[ne];
        }
        return t[p].cnt;
    }
};