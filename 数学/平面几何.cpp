using i64 = long long;
using l64 = long double;

template<class T>
struct Point {
    T x;
    T y;

    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }

    Point &operator+=(Point p) &{
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(Point p) &{
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point &operator*=(T v) &{
        x *= v;
        y *= v;
        return *this;
    }

    Point operator-() const {
        return Point(-x, -y);
    }

    friend Point operator+(Point a, Point b) {
        return a += b;
    }

    friend Point operator-(Point a, Point b) {
        return a -= b;
    }

    friend Point operator*(Point a, T b) {
        return a *= b;
    }

    friend Point operator*(T a, Point b) {
        return b *= a;
    }

    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }

    friend bool operator<(Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }

    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << p.x << " " << p.y;
    }
};

//角度转弧度
long double change(l64 d) {
    return acos(-1.0) / 180 * d;
}

template<class T>
T dot(Point<T> a, Point<T> b) {//计算两个点之间的点积。
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {//计算两个点之间的叉积
    return a.x * b.y - a.y * b.x;
}

template<class T>
T square(Point<T> p) {//计算一个点与其自身的点积
    return dot(p, p);
}

template<class T>
double length(Point<T> p) {//计算一个点表示的向量的长度
    return std::sqrt(double(square(p)));
}

long double length(Point<long double> p) {
    return std::sqrt(square(p));
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;

    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}

    friend std::istream &operator>>(std::istream &is, Line &l) {
        return is >> l.a.x >> l.a.y >> l.b.x >> l.b.y;
    }
};

template<class T>
T dist(Point<T> p, Line<T> line) {// 计算点道线段的距离
    if (line.a == line.b) {
        return dist(p, line.a);
    }
    Point<T> p1 = line.b - line.a, p2 = p - line.a, p3 = p - line.b;
    if (dot(p1, p2) < 0) return length(p2);
    if (dot(p1, p3) > 0) return length(p3);

    return std::abs(cross(line.b - line.a, p - line.a) / length(line.b - line.a));
}

template<class T>
T dist(Point<T> a, Point<T> b) {//计算两点之间的距离
    return std::hypot(a.x - b.x, a.y - b.y);
}

template<class T>
T dist2(Point<T> a, Point<T> b) {//计算两点之间距离的平方
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template<class T>
T dist(Line<T> line) {//计算直线的距离
    return std::hypot(line.a.x - line.b.x, line.a.y - line.b.y);
}

template<class T>
T PointToLine(Point<T> p, Line<T> l) { //点到直线的距离
    return std::abs(cross(p - l.a, l.b - l.a) / dist(l));
}

template<class T>
Point<T> shadowPointToLine(Point<T> p, Line<T> line) {//点在直线上的投影
    Point<T> v = line.b - line.a, u = p - line.a;
    return line.a + v * (dot(v, u) / square(v));
}

template<class T>
Point<T> PointToSegment(Point<T> p, Line<T> l) {//线端上距离点最近的点
    l64 mn = dist(p, l);
    l64 d1 = dist(p, l.a), d2 = dist(p, l.b);
    if (d1 == mn) {
        return l.a;
    } else if (d2 == mn) {
        return l.b;
    }
    return shadowPointToLine(p, l);
}

template<class T>
Point<T> rotate(Point<T> a, l64 d = 90) {//将一个点绕原点旋转 d 度（逆时针）
    d = change(d);
    return Point(a.x * std::cos(d) - std::sin(d) * a.y, std::sin(d) * a.x + std::cos(d) * a.y);
}

//根据点的位置（相对于原点）返回一个符号值。如果点在 x 轴上方（或在 x 轴上但 y = 0 且 x > 0），则返回 1；否则返回 -1。
template<class T>
int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {//判断点 p 是否在线段 l 的左侧（不包括线段上）。
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
bool pointOnLineRight(Point<T> p, Line<T> l) {//判断点 p 是否在线段 l 的左侧（不包括线段上）。
    return cross(l.b - l.a, p - l.a) < 0;
}

template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) {//计算两条线段 l1 和 l2 的交点。
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool pointOnSegment(Point<T> p, Line<T> l) {//判断点 p 是否在线段 l 上（包括端点）。
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
           && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<class T>
bool pointInPolygon(Point<T> a, std::vector<Point<T>> p) {//判断点 a 是否在多边形 p 内部。
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }

    return t == 1;
}

template<class T>
std::vector<Point<T>> Andrew(std::vector<Point<T>> p) {//求凸包
    std::sort(p.begin(), p.end(), [&](Point<T> x, Point<T> y) {
        return x.x != y.x ? x.x < y.x : x.y < y.y;
    });
    if (p.size() <= 2) return p;
    std::vector<Point<T>> stk;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        while (stk.size() > 1 && cross(stk.back() - stk[stk.size() - 2], p[i] - stk[stk.size() - 2]) <= 0)
            stk.pop_back();
        stk.push_back(p[i]);
    }
    int tmp = stk.size();
    for (int i = n - 2; i >= 0; i--) {
        while (stk.size() > tmp && cross(stk.back() - stk[stk.size() - 2], p[i] - stk[stk.size() - 2]) <= 0)
            stk.pop_back();
        stk.push_back(p[i]);
    }
    stk.pop_back();
    return stk;
}

template<class T>
std::pair<Point<T>, Point<T>> rotatingCalipers(std::vector<Point<T>> &p) {//旋转卡壳求最远点对距离
    T res = 0;
    std::pair<Point<T>, Point<T>> ans;
    int n = p.size();
    for (int i = 0, j = 1; i < n; i++) {
        while (cross(p[i + 1] - p[i], p[j] - p[i]) < cross(p[i + 1] - p[i], p[j + 1] - p[i])) j = (j + 1) % n;
        if (square(p[i] - p[j]) > res) {
            ans = {p[i], p[j]};
            res = square(p[i] - p[j]);
        }
        if (square(p[i + 1] - p[j]) > res) {
            ans = {p[i + 1], p[j]};
            res = square(p[i + 1] - p[j]);
        }
    }
    return ans;
}

// 0 : not intersect不相交
// 1 : strictly intersect严格相交
// 2 : overlap重叠
// 3 : intersect at endpoint在端点相交
//判断两条线段 l1 和 l2 是否相交，
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(Line<T> l1, Line<T> l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);

    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }

    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

//判断一条线段 l 是否完全位于一个多边形 p 内部
template<class T>
bool segmentInPolygon(Line<T> l, std::vector<Point<T>> p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));

        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

template<class T>
std::vector<Point<T>> hp(std::vector<Line<T>> lines) {
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;

        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }

        return cross(d1, d2) > 0;
    });

    std::deque<Line<T>> ls;
    std::deque<Point<T>> ps;
    for (auto l: lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }

        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }

        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }

        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {

                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }

        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }

    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(lineIntersection(ls[0], ls.back()));

    return std::vector(ps.begin(), ps.end());
}

//计算覆盖所有点的矩形的最小面积
template<class T>
T MinRectangeCover(std::vector<Point<T>> P) {
    int n = P.size();
    if (n < 3) return 0;
    P.push_back(P[0]);
    T ans = std::numeric_limits<T>::max();
    for (int i = 0, r = 1, p = 1, q; i < n; i++) {
        while (cross(P[i + 1] - P[i], P[r] - P[i]) < cross(P[i + 1] - P[i], P[r + 1] - P[i])) r = (r + 1) % n;
        while (dot(P[i + 1] - P[i], P[p] - P[i]) <= dot(P[i + 1] - P[i], P[p + 1] - P[i])) p = (p + 1) % n;
        if (i == 0) q = p;
        while (dot(P[i + 1] - P[i], P[q] - P[i]) >= dot(P[i + 1] - P[i], P[q + 1] - P[i])) q = (q + 1) % n;
        T d = square(P[i] - P[i + 1]);
        T tmp = cross(P[i + 1] - P[i], P[r] - P[i]) / d *
                (dot(P[i + 1] - P[i], P[p] - P[i]) - dot(P[i + 1] - P[i], P[q] - P[i]));
        if (ans > tmp) ans = tmp;
    }
    return ans;
}

//计算两个凸包之间的最短距离
template<class T>
T caliper(std::vector<Point<T>> a, std::vector<Point<T>> b) {
    auto calc = [&](std::vector<Point<T>> &p1, std::vector<Point<T>> &p2) {
        int n = p1.size() - 1, m = p2.size() - 1;
        int mn = 0, mx = 0;
        for (int i = 0; i < n; i++) if (p1[mn].y > p1[i].y) mn = i;
        for (int i = 0; i < m; i++) if (p2[mx].y < p2[i].y) mx = i;
        T ans = std::numeric_limits<T>::max();
        for (int i = 0; i < n; i++) {
            while (cross(p1[mn + 1] - p1[mn], p2[mx + 1] - p1[mn]) > cross(p1[mn + 1] - p1[mn], p2[mx] - p1[mn]))
                mx = (mx + 1) % m;
            ans = std::min({ans, dist(p1[mn], Line{p2[mx], p2[mx + 1]}), dist(p1[mn + 1], Line{p2[mx], p2[mx + 1]}),
                            dist(p2[mx], Line{p1[mn], p1[mn + 1]}), dist(p2[mx + 1], Line{p1[mn], p1[mn + 1]})});
            mn = (mn + 1) % n;
        }
        return ans;
    };
    a.push_back(a[0]);
    b.push_back(b[0]);
    return std::min(calc(a, b), calc(b, a));
}

//从平面的点组成的三角形面积的最小最大值(n^2log)
template<class T>
std::pair<T, T> minmaxTriangle(std::vector<Point<T>> p) {
    if (p.size() <= 2) return {0, 0};
    std::vector<std::pair<int, int>> evt;
    evt.reserve(p.size() * p.size());
    T t = std::abs(cross(p[0] - p[1], p[0] - p[2]));
    T min = t, max = t;
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < p.size(); j++) {
            if (i == j || p[i] == p[j]) continue;
            evt.emplace_back(i, j);
        }
    }
    auto cmp = [&](Point<T> x, Point<T> y) -> bool {
        auto calc = [&](Point<T> tmp) {
            if (tmp.y < 0) return 1;
            if (tmp.y > 0) return 4;
            if (tmp.x < 0) return 5;
            if (tmp.x > 0) return 3;
            return 2;
        };
        int t1 = calc(x), t2 = calc(y);
        if (t1 != t2) return t1 < t2;
        T t = cross(x, y);
        return t > 0;
    };
    std::sort(evt.begin(), evt.end(), [&](auto x, auto y) {
        Point<T> du = p[x.second] - p[x.first], dv = p[y.second] - p[y.first];
        std::swap(du.x, du.y), std::swap(dv.y, dv.x);
        du.x *= -1, dv.x *= -1;
        return cmp(du, dv);
    });
    std::vector<int> vx(p.size()), pos(p.size());
    for (int i = 0; i < p.size(); i++) vx[i] = i;
    std::sort(vx.begin(), vx.end(), [&](int x, int y) {
        return p[x].x == p[y].x ? p[x].y < p[y].y : p[x].x < p[y].x;
    });
    for (int i = 0; i < vx.size(); i++) pos[vx[i]] = i;
    for (auto [u, v]: evt) {
        int i = pos[u], j = pos[v];
        if (i > j) std::swap(u, v), std::swap(i, j);
        Point<T> pu = p[u], pv = p[v];
        if (i > 0) min = std::min(min, std::abs(cross(p[vx[i - 1]] - pu, p[vx[i - 1]] - pv)));
        if (j < vx.size() - 1) min = std::min(min, std::abs(cross(p[vx[j + 1]] - pu, p[vx[j + 1]] - pv)));
        max = std::max({max, std::abs(cross(p[vx[0]] - pu, p[vx[0]] - pv)),
                        std::abs(cross(p[vx.back()] - pu, p[vx.back()] - pv))});
        std::swap(vx[i], vx[j]);
        pos[u] = j, pos[v] = i;
    }
    return {min, max};
}

template<class T>
T PolygonArea(std::vector<Point<T>> p) {
    int n = p.size();
    if (n < 3) return 0;
    T s = p[0].y * (p[n - 1].x - p[1].x);
    for (int i = 1; i < n; i++) {
        s += p[i].y * (p[i - 1].x - p[(i + 1) % n].x);
    }
    return std::abs(s / 2);
}

template<class T>
T TriangleArea(Point<T> p1, Point<T> p2, Point<T> p3) {
    return std::abs(cross(p2 - p1, p3 - p1) / 2);
}

template<class T>
std::pair<Point<T>, Point<T>> nearestPoint(std::vector<Point<T>> &p) {
    std::sort(p.begin(), p.end());
    std::pair<Point<T>, Point<T>> ans;
    T d = std::numeric_limits<T>::max();
    std::vector<Point<T>> tmp;
    std::function<T(int, int)> dfs = [&](int l, int r) -> T {
        if (l == r) return std::numeric_limits<T>::max();
        if (l + 1 == r) {
            T d1 = dist2(p[l], p[r]);
            if (d1 < d) {
                ans = {p[l], p[r]},d = d1;
            }
            return d1;
        }
        int m = (l + r) >> 1;
        T d1 = std::min(dfs(l, m), dfs(m + 1, r));
        tmp.clear();
        for (int i = l; i <= r; i++) {
            if (std::abs(p[i].x - p[m].x) < d) tmp.emplace_back(p[i]);
        }
        std::sort(tmp.begin(), tmp.end(), [&](auto x, auto y) {
            return x.y < y.y;
        });
        for (int i = 0; i < tmp.size(); i++) {
            for (int j = i + 1; j < tmp.size() && tmp[j].y - tmp[i].y < d; j++) {
                if (dist2(tmp[i], tmp[j]) < d1) {
                    d1 = dist2(tmp[i], tmp[j]);
                    if (d > d1) {
                        d = d1, ans = {tmp[i], tmp[j]};
                    }
                }
            }
        }
        return d1;
    };
    dfs(0, p.size() - 1);
    return ans;
}