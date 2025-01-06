//改成ull会快很多
using i64 = long long;
std::vector<i64> M = {1610612741, 0, 805306457, 402653189, 201326611, 100663319, 50331653, 1000000007, 1000000009};

template<class T>
struct Hash {
    int n{}, m{};
    std::vector<i64> P1, P2;
    std::vector<std::vector<i64>> H;
    i64 p1 = 131, p2 = 13331;

    Hash() {};

    Hash(std::vector<std::vector<T>> &s) { Init(s); }

    void change() {
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (M[1] == 0) shuffle(M.begin(), M.end(), rng);
    }

    void Init(std::vector<std::vector<T>> &s) {
        if (M[1] == 0) change();
        n = s.size(), m = s[0].size();
        P1.resize(n + 1);
        P2.resize(m + 1);
        H.resize(n + 1);
        P1[0] = 1;
        P2[0] = 1;
        H[0].assign(m + 1, {});
        for (int i = 1; i <= n; i++) P1[i] = P1[i - 1] * p1 % M[1];
        for (int i = 1; i <= m; i++) P2[i] = P2[i - 1] * p2 % M[1];

        for (int i = 1; i <= n; i++) {
            H[i].assign(m + 1, {});
            for (int j = 1; j <= m; j++) {
                H[i][j] = (((((H[i - 1][j] * p1) % M[1]) + ((H[i][j - 1] * p2) % M[1])) % M[1] + s[i - 1][j - 1] -
                            ((H[i - 1][j - 1] * p1 % M[1]) * p2) % M[1]) % M[1] + M[1]) % M[1];

            }
        }
    }

    i64 get(int x1, int y1, int x2, int y2) {
        return ((H[x2][y2] - (H[x1 - 1][y2] * P1[x2 - x1 + 1] % M[1]) - (H[x2][y1 - 1] * P2[y2 - y1 + 1] % M[1])
                 + (((H[x1 - 1][y1 - 1] * P1[x2 - x1 + 1] % M[1]) * P2[y2 - y1 + 1] % M[1]) % M[1])) % M[1] + M[1]) %
               M[1];
    }
};