using i64 = long long;
std::vector<i64> M = {1610612741, 0, 805306457, 402653189, 201326611, 100663319, 50331653, 1000000007, 1000000009};

struct HASH {
    i64 h1 = 0, h2 = 0;

    HASH operator-(const HASH &x) const { return {h1 - x.h1, h2 - x.h2}; }

    HASH operator+(const HASH &x) const { return {h1 + x.h1, h2 + x.h2}; }

    HASH operator+(const std::pair<int, int> &x) const { return {h1 + x.first, h2 + x.second}; }

    HASH operator%(const std::pair<int, int> &x) const { return {h1 % x.first, h2 % x.second}; }

    bool operator==(const HASH &x) const { return h1 == x.h1 && h2 == x.h2; }

    bool operator<(const HASH &x) const { return h1 < x.h1 || (h1 == x.h1 && h2 < x.h2); }

    bool operator>(const HASH &x) const { return h1 > x.h1 || (h1 == x.h1 && h2 > x.h2); }
};

template<class T>
struct Hash {
    int n{};
    std::vector<i64> P1, P2;
    std::vector<HASH> H;
    i64 p1 = 131, p2 = 13331;

    Hash() {};

    Hash(std::string &s) { Init(s); }

    Hash(std::vector<T> &s) { Init(s); }

    void change() {
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (M[1] == 0 || M[2] == 0) shuffle(M.begin(), M.end(), rng);
    }

    void deal(int st, int len, std::vector<T> &s) {
        P1.resize(len + 1);
        P2.resize(len + 1);
        H.resize(len + 1);
        P1[0] = 1;
        P2[0] = 1;
        for (int i = st; i <= len; i++) {
            P1[i] = (P1[i - 1] * p1) % M[1];
            P2[i] = (P2[i - 1] * p2) % M[2];
            H[i].h1 = (H[i - 1].h1 * p1 + s[i - st + 1]) % M[1];
            H[i].h2 = (H[i - 1].h2 * p2 + s[i - st + 1]) % M[2];
        }
    }

    void Init(std::string &s) {
        std::vector<char> str(1, ' ');
        for (char &c: s)str.push_back(c);
        Init(str);
    }

    void Init(std::vector<T> &s) {
        if (M[1] == 0) change();
        n = s.size() - 1;
        deal(1, n, s);
    }

    HASH get(int l, int r) {
        HASH res;
        res.h1 = ((H[r].h1 - H[l - 1].h1 * P1[r - l + 1]) % M[1] + M[1]) % M[1];
        res.h2 = ((H[r].h2 - H[l - 1].h2 * P2[r - l + 1]) % M[2] + M[2]) % M[2];
        return res;
    }

    HASH mul(int l1, int r1, int l2, int r2) {
        HASH it1 = get(l1, r1), it2 = get(l2, r2), it3;
        it1.h1 *= P1[r2 - l2 + 1] %= M[1];
        it1.h2 *= P2[r2 - l2 + 1] %= M[2];
        it3 = (it1 + it2) % getMod();
        return it3;
    }

    HASH mul(HASH l, HASH r, int len) {
        HASH res;
        l.h1 *= P1[len] %= M[1];
        l.h2 *= P2[len] %= M[2];
        res = (l + r) % getMod();
        return res;
    }

    void push_back(std::string s) { push_back(std::vector<char>(s.begin(), s.end())); }

    void push_back(std::vector<T> s) { deal(n + 1, s.size() + n, s), n += s.size(); }

    std::pair<i64, i64> getMod() { return std::make_pair(M[1], M[2]); }
};