一些功能：
假设我们有一个串S，S下标从0开始：

1.求串S前缀0~i内本质不同回文串的个数（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同）

2.求串S内每一个本质不同回文串出现的次数

3.求串S内回文串的个数（其实就是1和2结合起来）

4.求以下标i结尾的回文串的个数

struct PAM {
    static constexpr int ALPHABET_SIZE = 26;

    struct Node {
        int len;
        int link;
        int cnt;
        int nums;
        std::array<int, ALPHABET_SIZE> next;

        Node() : nums{}, len{}, link{}, cnt{}, next{} {}
    };

    std::vector<Node> t;
    int suff;
    std::string s;

    PAM() {
        init();
    }

    void init() {
        t.assign(2, Node());
        t[1].len = -1;
        t[1].link = 0;
        t[0].link = 1;
        suff = 0;
        s = " ";
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int getlink(int x, int n) {
        while (s[n - len(x) - 1] != s[n]) x = link(x);
        return x;
    }

    void add(char c, char offset = 'a') {
        int pos = s.size();
        s += c;
        int let = c - offset;
        int cur = getlink(suff, pos);

        if (!next(cur, let)) {
            int p = newNode();
            t[p].link = next(getlink(link(cur), pos), let);
            t[p].len = t[cur].len + 2;
            t[cur].next[let] = p;
        }
        suff = next(cur, let);
        t[suff].nums = t[link(suff)].nums + 1;
        t[suff].cnt++;
    }

    int size() { return t.size(); }

    int nums(int p) { return t[p].nums; }

    int len(int p) { return t[p].len; }

    int link(int p) { return t[p].link; }

    int cnt(int p) { return t[p].cnt; }

    int next(int p, int c) { return t[p].next[c]; };
};
