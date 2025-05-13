std::vector<std::array<int, 26>> init(std::string &s) {
    int n = s.size();
    std::vector<std::array<int, 26>> next(n + 1);
    next[n].fill(n);
    for (int i = n - 1; i >= 0; i--) {
        next[i] = next[i + 1];
        next[i][s[i] - 'a'] = i;
    }
    return next;
}

bool isSequence(const std::vector<std::array<int, 26>> &next, const std::string &s) {
    int p = -1;
    for (char i : s) {
        int np = next[p + 1][i - 'a'];
        if (np >= next.size() - 1) return false;
        p = np;
    }
    return true;
}