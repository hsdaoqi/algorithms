std::vector<int> kmp(std::string &s) {
    int n = s.size();
    std::vector<int> next(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = next[j];
        if (s[i] == s[j]) j++;
        next[i + 1] = j;
    }
    return next;
}