//线性基
template<class T>
struct LineBasis {
    const int MAXL = std::__lg(std::numeric_limits<T>::max());
    std::vector<T> a;
    int Linetot, Arrtot;

    LineBasis operator+(const LineBasis &other) {
        for (int i = 0; i <= MAXL; i++) insert(other.a[i]);
        return this;
    }

    LineBasis() {
        Linetot = Arrtot = 0;
        a.resize(MAXL + 1);
    }

    LineBasis(std::vector<T> &x) {
        Linetot = Arrtot = 0;
        a.resize(MAXL + 1);
        build(x, x.size() - 1);
    }

    bool insert(T val) {//插入，判断一个数是否可以异或出来
        Arrtot++;
        for (int j = MAXL; j >= 0; j--) {
            if (!val) return false;
            if (!(val & (1ll << j))) continue;
            if (a[j]) {
                val ^= a[j];
            } else {//插入的时候直接修改，在求第k小时就不用改了
                for (int k = 0; k < j; k++) {
                    if (val & (1ll << k)) val ^= a[k];
                }
                for (int k = j + 1; k <= MAXL; k++) {
                    if (a[k] & (1ll << j)) a[k] ^= val;
                }
                a[j] = val, Linetot++;
                break;
            }
        }
        return true;
    }

    bool find(T x) {
        for (int i = 5; i >= 0; i--) {
            if (x >> i & 1) {
                if (!a[i]) break;
                x ^= a[i];
            }
        }
        return x == 0;
    }

    void build(std::vector<T> &x, int n) {
        for (int i = 1; i <= n; i++) insert(x[i]);
    }

    T largest() {
        T res = 0;
        for (int i = 0; i <= MAXL; i++) res ^= a[i];
        return res;
    }

    T smallest() {
        if (Linetot < Arrtot) return 0;
        for (int i = 0; i <= MAXL; i++) if (a[i]) return a[i];
    }

    T smallest(T k) {
        if (k == 1 && Linetot < Arrtot)return 0;
        if (Linetot < Arrtot) k--;
        if (k >= 1ll << Linetot) return -1;
        T ans = 0;
        for (int i = 0; i <= MAXL; i++) {
            if (a[i] != 0) {
                if (k & 1) ans ^= a[i];
                k /= 2;
            }
        }
        return ans;
    }
};