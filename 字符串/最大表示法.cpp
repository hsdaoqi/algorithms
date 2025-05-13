int minp(std::string &s) {
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        for (k = 0; k < n && s[(i + k) % n] == s[(j + k) % n]; k++);
        s[(i + k) % n] > s[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
        if (i == j) i++;
    }
    return std::min(i, j);
}