//bsgs
//a^x=b(mod p),求最小的非负整数x（a,p互质）
//根据扩展欧拉定理a^x=a^(x%phi(p)) (mod p),可知a^x模p意义下的最小循环节为phi(p)
//令x=im-j,其中m=ceil(sqrt(p)),i~(1--m),j~(0,m-1)



template<class T>
struct BSGS {
    T bsgs(T a, T b, T p) {
        a %= p, b %= p;
        if (b == 1) return 0;
        T m = ceil(sqrt((double) p)), t = b;
        std::map<T, int> doc; doc[b] = 0;
        for (int i = 1; i < m; i++) {
            t = t * a % p;
            doc[t] = i;
        }
        T mi = 1; t = 1;
        for (int i = 1; i <= m; i++) mi = mi * a % p;

        for (int i = 1; i <= m; i++) {
            t = t * mi % p;
            if (doc.count(t)) return i * m - doc[t];
        }
        return -1;
    }

    T exbsgs(T a, T b, T p) {
        a %= p, b %= p;
        if (b == 1 || p == 1) return 0;
        T k = 0, A = 1;
        while (true) { //使a,p互质
            T g = __gcd(a, p);
            if (g == 1) break;
            if (b % g != 0) return -1;
            k++, b /= g, p /= g;
            A = A * (a / g) % p;
            if (A == b) return k;
        }
        T m = ceil(sqrt((double) p)), t = b;
        std::map<T, int> doc; doc[t] = 0;
        for (int i = 1; i < m; i++) {
            t = t * a % p;
            doc[t] = i;
        }
        T mi = 1;t = A;
        for (int i = 1; i <= m; i++) mi = mi * a % p;
        for (int i = 1; i <= m; i++) {
            t = t * mi % p;
            if (doc.count(t)) return i * m - doc[t] + k;
        }
        return -1;
    }
};