//扩展欧几里得算法
//求出a*x+b*y=gcd(a,b)式子中，满足条件的x与y,同时求出gcd(a,b);

//x,y为经过运算最初得到的数
//先求特解(x0,y0)-->x0==x*c/gcd,y0==y*c/gcd;
//再构造通解X=x0+(b*k)/gcd(a,b),Y=y0-(a*k)/gcd(a,b)
//最小正整数解Xmin == (x0%(b/g)+(b/g))%(b/g) ,Ymin=(y0%(a/g)+(a/g))%(a/g)

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 gcd = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}
