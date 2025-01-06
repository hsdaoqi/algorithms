std::vector<int> Zfunc(std::string s) {
    int n = s.size();
    s = " " + s;
    std::vector<int> z(n + 1);
    z[1] = n;
    for (int i = 2, l, r = 0; i <= n; i++) {
        if (i <= r) z[i] = std::min(z[i - l + 1], r - i + 1);
        while (s[1 + z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}