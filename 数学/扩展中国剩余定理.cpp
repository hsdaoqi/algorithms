template<class T>
T exgcd(T a, T b, __int128 &x, __int128 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    T gcd = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

template<class T>
T EXCRT(const std::vector<T> &m, const std::vector<T> &r) { //有x=r1(mod m1),x=r2(mod m2)
    __int128 m1, m2, r1, r2, p, q;                //转化为x=m1*p+r1=m2*q+r2  (1)
    m1 = m[0], r1 = r[0];                   //m1*p-m2*q=r2-r1
    int n = m.size();
    for (int i = 1; i < n; i++) {
        m2 = m[i], r2 = r[i];
        __int128 d = exgcd(m1, m2, p, q);
        if ((r2 - r1) % d) { return -1; }      //由裴蜀定理-->> 当gcd(m1,m2)|(r2-r1)时 有解
        p = p * (r2 - r1) / d;//特解            //由扩欧算法得 特解p=p*(r2-r1)/gcd,q=q*(r2-r1)/gcd
        p = (p % (m2 / d) + m2 / d) % (m2 / d);//p可能是负数，为了方便要使p变成正数,通解--》P=p+m2/gcd*k,Q=q-m1/gcd*k
        r1 = m1 * p + r1;                     //x=m1*P+r1=(m1*m2)/gcd*k+m1*p1+r1,与（1）比对
        m1 = m1 * m2 / d;                      //得r=m1*p+r1,m=lcm(m1,m2)
    }
    return (r1 % m1 + m1) % m1;
}