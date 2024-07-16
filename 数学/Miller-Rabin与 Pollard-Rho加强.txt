template <typename _ModType>
struct Barrett {
    _ModType m_P;
    __uint128_t m_Pinv;
    constexpr Barrett() = default;
    constexpr explicit Barrett(_ModType __P) : m_P(__P), m_Pinv(-uint64_t(__P) / __P + 1) {}
    constexpr _ModType mod() const { return m_P; }
    constexpr _ModType mod(uint64_t __a) const {
        __a -= uint64_t(m_Pinv * __a >> 64) * m_P + m_P;
        if (__a >= m_P) __a += m_P;
        return __a;
    }
    constexpr _ModType plus(_ModType __a, _ModType __b) {
        if (__a += __b; __a >= m_P) __a -= m_P;
        return __a;
    }
    constexpr _ModType minus(_ModType __a, _ModType __b) {
        if (__a += m_P - __b; __a >= m_P) __a -= m_P;
        return __a;
    }
    constexpr _ModType multiply(uint64_t __a, uint64_t __b) const {
        if constexpr (std::is_same_v<_ModType, uint64_t>)
            return multiply_ld(__a, __b);
        else
            return multiply_64(__a, __b);
    }
    constexpr _ModType multiply_64(uint64_t __a, uint64_t __b) const {
        // assert(__a * __b < 1ull << 64);
        return mod(__a * __b);
    }
    constexpr _ModType multiply_128(uint64_t __a, uint64_t __b) const {
        return __uint128_t(__a) * __b % m_P;
    }
    constexpr _ModType multiply_ld(uint64_t __a, uint64_t __b) const {
        // assert(m_P < 1ull << 63 && __a < m_P && __b < m_P);
        int64_t res = __a * __b - uint64_t(1.L / m_P * __a * __b) * m_P;
        if (res < 0)
            res += m_P;
        else if (res >= m_P)
            res -= m_P;
        return res;
    }
    constexpr _ModType pow(uint64_t __a, uint64_t __n) const {
        if constexpr (std::is_same_v<_ModType, uint64_t>)
            return pow_ld(__a, __n);
        else
            return pow_64(__a, __n);
    }
    constexpr _ModType pow_64(uint64_t __a, uint64_t __n) const {
        // assert(m_P < 1ull << 32);
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_64(res, b);
            b = multiply_64(b, b);
            __n >>= 1;
        }
        return res;
    }
    constexpr _ModType pow_128(uint64_t __a, uint64_t __n) const {
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_128(res, b);
            b = multiply_128(b, b);
            __n >>= 1;
        }
        return res;
    }
    constexpr _ModType pow_ld(uint64_t __a, uint64_t __n) const {
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_ld(res, b);
            b = multiply_ld(b, b);
            __n >>= 1;
        }
        return res;
    }
    template <typename _Tp>
    constexpr _Tp divide(_Tp __a) const {
        if (__a < m_P) return 0;
        _Tp res = m_Pinv * __a >> 64;
        if (__a - res * m_P >= m_P) res++;
        return res;
    }
    template <typename _Tp>
    constexpr std::pair<_Tp, _Tp> divmod(_Tp __a) const {
        _Tp quo = (__a * m_Pinv) >> 64, rem = __a - quo * m_P;
        if (rem >= m_P) {
            quo++;
            rem -= m_P;
        }
        return {quo, rem};
    }
};
using Barrett32 = Barrett<uint32_t>;
using Barrett64 = Barrett<uint64_t>;
template <typename _ModType>
struct _MontgomeryTag;
template <>
struct _MontgomeryTag<uint32_t> {
    using long_type = uint64_t;
    static constexpr uint32_t limit = (1u << 31) - 1;
    static constexpr uint32_t inv_loop = 4;
    static constexpr uint32_t length = 32;
};
template <>
struct _MontgomeryTag<uint64_t> {
    using long_type = __uint128_t;
    static constexpr uint64_t limit = (1ull << 63) - 1;
    static constexpr uint32_t inv_loop = 5;
    static constexpr uint32_t length = 64;
};
template <typename _ModType>
struct Montgomery {
    using _FastType = _ModType;
    using _LongType = typename _MontgomeryTag<_ModType>::long_type;
    _ModType m_P;
    _ModType m_Pinv;
    _ModType m_Ninv;
    Barrett<_ModType> m_brt;
    constexpr Montgomery() = default;
    constexpr explicit Montgomery(_ModType __P) : m_P(__P), m_Pinv(__P), m_Ninv(-_LongType(__P) % __P), m_brt(__P) {
        // assert((__P & 1) && __P > 1 && __P <= _MontgomeryTag<_ModType>::limit);
        for (int i = 0; i < _MontgomeryTag<_ModType>::inv_loop; i++) m_Pinv *= _ModType(2) - __P * m_Pinv;
    }
    constexpr _ModType mod() const { return m_brt.mod(); }
    constexpr _ModType mod(uint64_t __a) const { return m_brt.mod(__a); }
    constexpr _FastType init(uint64_t __a) const { return reduce(_LongType(mod(__a)) * m_Ninv); }
    constexpr _FastType raw_init(uint64_t __a) const { return reduce(_LongType(__a) * m_Ninv); }
    constexpr _FastType reduce(_LongType __a) const {
        _FastType res = (__a >> _MontgomeryTag<_ModType>::length) - _ModType(_LongType(_ModType(__a) * m_Pinv) * m_P >> _MontgomeryTag<_ModType>::length);
        if (res >= mod()) res += mod();
        return res;
    }
    constexpr _ModType reduce(_FastType __a) const {
        _ModType res = -_ModType(_LongType(__a * m_Pinv) * m_P >> _MontgomeryTag<_ModType>::length);
        if (res >= mod()) res += mod();
        return res;
    }
    constexpr _FastType plus(_FastType __a, _FastType __b) const {
        if (__a += __b; __a >= m_P) __a -= m_P;
        return __a;
    }
    constexpr _FastType minus(_FastType __a, _FastType __b) const {
        if (__a += m_P - __b; __a >= m_P) __a -= m_P;
        return __a;
    }
    constexpr _FastType multiply(_FastType __a, _FastType __b) const { return reduce(_LongType(__a) * __b); }
    constexpr _FastType pow(_FastType __a, uint64_t __n) const {
        _FastType res = reduce(_LongType(1) * m_Ninv);
        while (__n) {
            if (__n & 1) res = multiply(res, __a);
            __a = multiply(__a, __a);
            __n >>= 1;
        }
        return res;
    }
    template <typename _Tp>
    constexpr _Tp divide(_Tp __a) const { return m_brt.divide(__a); }
    template <typename _Tp>
    constexpr std::pair<_Tp, _Tp> divmod(_Tp __a) const { return m_brt.divmod(__a); }
};
using Montgomery32 = Montgomery<uint32_t>;
using Montgomery64 = Montgomery<uint64_t>;
template <typename _Elem>
constexpr bool isPrime(_Elem n) {
    if (std::is_same_v<_Elem, uint32_t> || n <= UINT32_MAX) {
        if (n <= 1) return false;
        if (n == 2 || n == 7 || n == 61) return true;
        if (n % 2 == 0) return false;
        Barrett32 brt(n);
        uint32_t d = (n - 1) >> std::__countr_zero(n - 1);
        for (auto &&a : {2, 7, 61}) {
            uint32_t s = d, y = brt.pow_64(a, s);
            while (s != n - 1 && y != 1 && y != n - 1) {
                y = brt.multiply_64(y, y);
                s <<= 1;
            }
            if (y != n - 1 && s % 2 == 0) return false;
        }
        return true;
    } else {
        // assert(n < 1ull < 63);
        if (n % 2 == 0) return false;
        Montgomery64 mg(n);
        uint64_t d = (n - 1) >> std::__countr_zero(n - 1), one = mg.init(1);
        for (auto &&a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            uint64_t s = d, y = mg.pow(mg.init(a), s), t = mg.init(n - 1);
            while (s != n - 1 && y != one && y != t) {
                y = mg.multiply(y, y);
                s <<= 1;
            }
            if (y != t && s % 2 == 0) return false;
        }
        return true;
    }
}
constexpr auto isPrime32 = isPrime<uint32_t>;
constexpr auto isPrime64 = isPrime<uint64_t>;
struct Pollard_Rho {
    static constexpr uint64_t batch = 128;
    static inline std::mt19937_64 s_rander = std::mt19937_64();
    template <typename _Elem>
    static _Elem pick(_Elem __n) {
        // assert(!isPrime<_Elem>(__n));
        if (__n % 2 == 0) return 2;
        static Montgomery<_Elem> mg;
        if (mg.mod() != __n) mg = Montgomery<_Elem>(__n);
        std::uniform_int_distribution<_Elem> distribute(2, __n - 1);
        _Elem v0, v1 = mg.init(distribute(s_rander)), prod = mg.init(1), c = mg.init(distribute(s_rander));
        for (int i = 1; i < batch; i <<= 1) {
            v0 = v1;
            for (int j = 0; j < i; j++) v1 = mg.multiply(v1, v1) + c;
            for (int j = 0; j < i; j++) {
                v1 = mg.multiply(v1, v1) + c;
                prod = mg.multiply(prod, v0 > v1 ? v0 - v1 : v1 - v0);
                if (!prod) return pick(__n);
            }
            if (_Elem g = std::gcd(prod, __n); g > 1) return g;
        }
        for (int i = batch;; i <<= 1) {
            v0 = v1;
            for (int j = 0; j < i; j++) v1 = mg.multiply(v1, v1) + c;
            for (int j = 0; j < i; j += batch) {
                for (int k = 0; k < batch; k++) {
                    v1 = mg.multiply(v1, v1) + c;
                    prod = mg.multiply(prod, v0 > v1 ? v0 - v1 : v1 - v0);
                    if (!prod) return pick(__n);
                }
                if (_Elem g = std::gcd(prod, __n); g > 1) return g;
            }
        }
        return __n;
    }
    template <typename _Elem>
    static auto decomposite(_Elem __n) {
        struct node {
            _Elem prime;
            uint32_t count;
        };
        std::vector<node> res;
        auto dfs = [&](auto self, _Elem cur) -> void {
            if (!isPrime<_Elem>(cur)) {
                _Elem a = pick<_Elem>(cur);
                self(self, a);
                self(self, cur / a);
            } else {
                auto find = std::find_if(res.begin(), res.end(), [cur](auto x) { return x.prime == cur; });
                if (find == res.end())
                    res.push_back({cur, 1u});
                else
                    find->count++;
            }
        };
        if (__n % 2 == 0) {
            res.push_back({2, uint32_t(std::__countr_zero(__n))});
            __n >>= std::__countr_zero(__n);
        }
        if (__n > 1) dfs(dfs, __n);
        std::sort(res.begin(), res.end(), [](auto &x, auto &y) { return x.prime < y.prime; });
        return res;
    }
    template <typename _Elem>
    static std::vector<_Elem> getFactors(_Elem __n) {
        auto pf = decomposite(__n);
        std::vector<_Elem> res;
        _Elem count = 1;
        for (auto [p, c] : pf) count *= c + 1;
        res.reserve(count);
        auto dfs = [&](auto self, int i, _Elem prod) -> void {
            if (i == pf.size())
                res.push_back(prod);
            else {
                auto [p, c] = pf[i];
                self(self, i + 1, prod);
                while (c--) self(self, i + 1, prod *= p);
            }
        };
        dfs(dfs, 0, 1);
        std::sort(res.begin(), res.end());
        return res;
    }
    template <typename _Elem>
    static _Elem EulerPhi(_Elem __n) {
        for (auto [p, c] : decomposite(__n)) __n = __n / p * (p - 1);
        return __n;
    }
};
