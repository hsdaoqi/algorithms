struct Bign {
    std::string a;

    Bign() = default;

    Bign(const Bign &rhs) : a(rhs.a) {}

    Bign(const long long &rhs) : a(std::to_string(rhs)) {}

    bool operator==(const Bign &rhs) const { return a == rhs.a; }

    bool operator==(const long long &rhs) const { return a == std::to_string(rhs); }

    bool operator>(const Bign &rhs) {
        if (*this == rhs) return false;
        if (a[0] == '-' && rhs.a[0] != '-') return false;
        if (a[0] != '-' && rhs.a[0] == '-') return true;
        if (a[0] == '-' && rhs.a[0] == '-') {
            if (a.size() > rhs.a.size()) return false;
            if (a.size() < rhs.a.size()) return true;
            return a < rhs.a;
        } else {
            if (a.size() < rhs.a.size()) return false;
            if (a.size() > rhs.a.size()) return true;
            return a > rhs.a;
        }
    }

    bool operator>=(const Bign &rhs) { return *this == rhs || *this > rhs; }

    bool operator<(const Bign &rhs) { return !(*this >= rhs); }

    bool operator<=(const Bign &rhs) { return *this == rhs || *this < rhs; }

    Bign operator=(const long long &rhs) {
        a = std::to_string(rhs);
        return *this;
    }

    friend Bign operator+(Bign lhs, Bign rhs) {
        lhs.a += std::string(10, 0), rhs.a += std::string(10, 0);
        Bign ans;
        bool fa = (lhs.a[0] == '-'), fb = (rhs.a[0] == '-');
        auto cmp = [&]() -> bool {
            int la = lhs.a.size() - 10, lb = rhs.a.size() - 10;
            if (la - fa > lb - fb) return 1;
            else if (la - fa < lb - fb) return 0;
            else {
                int i = 0;
                while (i < la && lhs.a[i + fa] == rhs.a[i + fb]) i++;
                return lhs.a[i + fa] > rhs.a[i + fb];
            }
        };

        if (!cmp()) std::swap(lhs.a, rhs.a), std::swap(fa, fb);
        int la = lhs.a.size() - 10, lb = rhs.a.size() - 10;
        std::reverse(lhs.a.begin() + fa, lhs.a.begin() + la);
        std::reverse(rhs.a.begin() + fb, rhs.a.begin() + lb);
        auto minu = [&]() {
            int i, j, c = 0, l = -1, s;
            for (i = 0; i + fa < la; i++) {
                s = lhs.a[i + fa] - rhs.a[i + fb] - c >= 0 ? 0 : 1;
                lhs.a[i + fa] = (10 + lhs.a[i + fa] - rhs.a[i + fb] - c) % 10;
                l = lhs.a[i + fa] ? i + fa : l, c = s;
            }
            if (l < 0) ans.a = '0';
            else {
                if (fa) ans.a = "-";
                for (int k = l; k >= fa; k--) ans.a += lhs.a[k] + '0';
            }
        };
        auto add = [&]() {
            int i, t = 0, s, l;
            for (i = fa; i < la || i < lb; i++) {
                s = lhs.a[i] + rhs.a[i] + t;
                t = s / 10;
                lhs.a[i] = s % 10;
            }
            lhs.a[i] = t;
            l = t ? i : i - 1;
            if (fa) ans.a = "-";
            for (int k = l; k >= fa; k--) ans.a += lhs.a[k] + '0';
        };
        int i = fa, j = fb;
        while (i < la) lhs.a[i] -= '0', i++;
        while (j < lb) rhs.a[j] -= '0', j++;
        if (fa ^ fb) minu();
        else add();
        return ans;
    }

    friend Bign operator-(Bign lhs, Bign rhs) {
        bool fa, fb;
        std::string s, t;
        Bign ans;
        auto init = [&]() {
            fa = (lhs.a[0] == '-'), fb = (rhs.a[0] == '-');
            s = lhs.a.substr(1, lhs.a.size()), t = rhs.a.substr(1, rhs.a.size());
        };
        auto cmp = [&](std::string &ta, std::string &tb) {
            int as = ta.size(), bs = tb.size();
            if (as > bs || as == bs && ta > tb) return 1;
            return 0;
        };
        auto change = [&](std::string &s, std::string &t, std::string a, std::string b) {
            int as = a.size(), bs = b.size(), d = as > bs ? as - bs : bs - as;
            for (int i = 0; i < d; i++) as > bs ? t += "0" : s += "0";
            s += a, t += b;
        };
        auto cA = [&](std::string a, std::string b) -> std::string {
            std::string s = "0", t = "0";
            change(s, t, a, b);
            int len = s.size();
            for (int i = len - 1; i >= 1; i--) {
                s[i] += t[i] - '0';
                if (s[i] > '9') s[i] -= 10, s[i - 1]++;
            }
            bool j = 1;
            for (int i = 0; i < len; i++)
                if (s[i] != '0') j = 0;
            if (j) return "0";
            return s[0] == '0' ? s.substr(1, len) : s;
        };
        auto cB = [&](std::string a, std::string b) -> std::string {
            std::string s = "", t = "";
            change(s, t, a, b);
            if (s < t) swap(s, t);
            int len = s.size();
            for (int i = len - 1; i >= 0; i--) {
                if (s[i] < t[i]) {
                    s[i] += 10;
                    if (s[i - 1] >= '1') s[i - 1]--;
                    else {
                        int j = i - 1;
                        while (s[j] == '0') s[j--] += 9;
                        s[j]--;
                    }
                }
                s[i] -= (t[i] - '0');
            }
            if (len == 1) return s;
            return s[0] == '0' ? cA(s.substr(1, len), "0") : s;
        };
        init();
        if (fa && fb) {
            if (cmp(s, t)) ans.a += '-';
            ans.a += cB(s, t);
        } else if (!fa && !fb) {
            if (!cmp(lhs.a, rhs.a)) ans.a += "-";
            ans.a += cB(lhs.a, rhs.a);
        } else if (fa) ans.a = "-" + cA(s, rhs.a);
        else ans.a = cA(lhs.a, t);
        fa = (ans.a[0] == '-');
        for (int i = fa; i < ans.a.size(); i++) {
            if (ans.a[i] != '0' || i == ans.a.size() - 1) {
                ans.a = (fa ? "-" : "") + ans.a.substr(i);
                break;
            }
        }
        if (ans.a == "-0") ans.a = '0';
        return ans;
    }

    friend Bign operator*(Bign lhs, Bign rhs) {
        Bign ans;
        int la = lhs.a.size(), lb = rhs.a.size();
        lhs.a += std::string(5, 0), rhs.a += std::string(5, 0);
        std::string c = std::string(lb + la + 5, 0);
        auto ta = lhs.a, tb = rhs.a;
        int f = 1, t = 0;
        if (lhs.a[0] == '-') f *= -1, t++;
        for (int i = t; i <= la - 1; i++) {
            lhs.a[la - i] = ta[i] - '0';
        }
        t = 0;
        if (rhs.a[0] == '-') f *= -1, t++;
        for (int i = t; i <= lb - 1; i++) {
            rhs.a[lb - i] = tb[i] - '0';
        }
        for (int i = 1; i <= la; i++) {
            int x = 0;
            for (int j = 1; j <= lb; j++) {
                c[i + j - 1] += lhs.a[i] * rhs.a[j] + x;
                x = c[i + j - 1] / 10;
                c[i + j - 1] %= 10;
            }
            c[i + lb] = x;
        }
        while (c.back() == 0 && c.size() > 2) c.pop_back();
        if (f == -1) ans.a += '-';
        for (int i = c.size() - 1; i >= 1; i--) ans.a += c[i] + '0';

        if (ans.a == "-0") ans.a = "0";
        return ans;
    }

    friend Bign operator/(Bign lhs, Bign rhs) {
        auto fixedNum = [&](std::string &a) -> std::string {
            if (a.size() == 1) return a;
            for (int i = 0; i < a.size(); i++) {
                if ('1' <= a[i] && a[i] <= '9') return a.substr(i, a.size());
            }
            return "0";
        };
        auto cA = [&](std::string a, std::string b) -> std::string {
            a = fixedNum(a), b = fixedNum(b);
            int as = a.size(), bs = b.size(), d = as > bs ? as - bs : bs - as;
            std::string s = "0", t = "0";
            for (int i = 0; i < d; i++) as > bs ? t += "0" : s += "0";
            s += a, t += b;
            for (int i = s.size() - 1; i >= 1; i--) {
                s[i] += t[i] - '0';
                if (s[i] > '9') s[i] -= 10, s[i - 1]++;
            }
            return s[0] == '0' ? s.substr(1, s.size()) : s;
        };
        auto cS = [&](std::string a, std::string b) -> std::string {
            int as = a.size(), bs = b.size(), d = as - bs;
            std::string s = "", t = "";
            for (int i = 0; i < d; i++) t += "0";
            s += a, t += b;
            for (int i = s.size() - 1; i >= 0; i--) {
                if (s[i] < t[i]) {
                    s[i] += 10;
                    if (s[i - 1] >= '1') s[i - 1]--;
                    else {
                        int j = i - 1;
                        while (s[j] == '0') s[j--] += 9;
                        s[j]--;
                    }
                }
                s[i] -= (t[i] - '0');
            }
            if (s.size() == 1) return s;
            for (int i = 0; i < s.size(); i++) {
                if ('1' <= s[i] && s[i] <= '9') return s.substr(i, s.size());
            }
            return "0";
        };
        Bign ans;
        std::string c, sum = "0", cnt = "1";
        bool j1 = 0;

        if (lhs.a == "0") {
            return ans = 0;
        } else if (lhs.a[0] == '-' && rhs.a[0] == '-') {
            lhs.a = lhs.a.substr(1, lhs.a.size()), rhs.a = rhs.a.substr(1, rhs.a.size());
        } else if (lhs.a[0] == '-') {
            j1 = 1, lhs.a = lhs.a.substr(1, lhs.a.size());
        } else if (rhs.a[0] == '-') {
            j1 = 1, rhs.a = rhs.a.substr(1, rhs.a.size());
        }
        c = rhs.a;
        int as = lhs.a.size(), bs = rhs.a.size(), cs, d = as - bs;
        for (int i = 0; i < d - 1; i++) c += "0", cnt += "0";
        cs = c.size();
        bool j2 = 0;
        while (c != rhs.a) {
            while (as > cs || as == cs && lhs.a >= c)
                j2 = 1, lhs.a = cS(lhs.a, c), as = lhs.a.size(), sum = cA(sum, cnt);
            c = c.substr(0, c.size() - 1), cnt = cnt.substr(0, cnt.size() - 1), cs = c.size();
        }
        while (as > bs || as == bs && lhs.a >= rhs.a)
            j2 = 1, lhs.a = cS(lhs.a, rhs.a), sum = cA(sum, cnt), as = lhs.a.size();
        if (j1 && j2) ans.a += '-';
        ans.a += sum;
        if (ans.a == "-0") ans.a = "0";
        return ans;
    }

    friend Bign operator%(Bign &lhs, Bign &rhs) {
        Bign ans;
        ans = lhs - rhs * (lhs / rhs);
        return ans;
    }

    Bign operator+=(Bign &rhs) {
        *this = *this + rhs;
        return *this;
    }

    Bign operator-=(Bign &rhs) {
        *this = *this - rhs;
        return *this;
    }

    Bign operator*=(Bign &rhs) {
        *this = *this * rhs;
        return *this;
    }

    Bign operator/=(Bign &rhs) {
        *this = *this / rhs;
        return *this;
    }

    Bign operator%=(Bign &rhs) {
        *this = *this % rhs;
        return *this;
    }

    friend std::istream &operator>>(std::istream &in, Bign &x) {
        in >> x.a;
        bool fa = (x.a[0] == '-');
        for (int i = fa; i < x.a.size(); i++) {
            if (x.a[i] != '0' || i == x.a.size() - 1) {
                x.a = (fa ? "-" : "") + x.a.substr(i);
                break;
            }
        }
        if (x.a == "-0") x.a = "0";
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Bign &x) {
        out << x.a;
        return out;
    }
};

using B = Bign;