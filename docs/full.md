- [算法竞赛模板](#算法竞赛模板)
  - [杂项](#杂项)
    - [快读](#快读)
    - [快速输出](#快速输出)
    - [二维差分](#二维差分)
    - [二维前缀和](#二维前缀和)
    - [进制背包 DP](#进制背包-dp)
    - [状态压缩 DP](#状态压缩-dp)
    - [数位 DP](#数位-dp)
  - [数论](#数论)
    - [位运算与集合操作](#位运算与集合操作)
    - [快速幂](#快速幂)
    - [乘法逆元（MOD为质数）](#乘法逆元mod为质数)
    - [最大公因数](#最大公因数)
    - [判断质数](#判断质数)
    - [扩展欧几里得](#扩展欧几里得)
    - [精确开平方](#精确开平方)
    - [欧拉筛（线性筛）](#欧拉筛线性筛)
    - [欧拉筛、莫比乌斯函数、杜教筛](#欧拉筛莫比乌斯函数杜教筛)
    - [组合数（阶乘逆元，MOD很大时适用，质数）](#组合数阶乘逆元mod很大时适用质数)
    - [线性基](#线性基)
  - [数据结构](#数据结构)
    - [并查集](#并查集)
    - [ST表](#st表)
    - [离散化](#离散化)
    - [前缀和正序对](#前缀和正序对)
    - [逆序对](#逆序对)
    - [树状数组](#树状数组)
    - [区间乘、区间加、区间赋值、最值查询、区间查询（Lazy线段树）](#区间乘区间加区间赋值最值查询区间查询lazy线段树)
    - [区间加等差数列 + 单点查询（线段树）](#区间加等差数列--单点查询线段树)
    - [莫队](#莫队)
  - [图论](#图论)
    - [拓扑排序](#拓扑排序)
    - [Dijkstra 单源最短路（朴素）](#dijkstra-单源最短路朴素)
    - [Dijkstra（邻接表 + 优先队列优化）](#dijkstra邻接表--优先队列优化)
    - [Floyd 多源最短路](#floyd-多源最短路)
    - [Bellman-Ford](#bellman-ford)
    - [最小生成树 Prim](#最小生成树-prim)
    - [最小生成树 Kruskal](#最小生成树-kruskal)
    - [SPFA 负环](#spfa-负环)
    - [LCA 倍增法](#lca-倍增法)
    - [树的直径](#树的直径)
    - [欧拉回路（Hierholzer）](#欧拉回路hierholzer)
    - [欧拉路（有向图）](#欧拉路有向图)
    - [二分图判定](#二分图判定)
    - [匈牙利算法](#匈牙利算法)
    - [树形 DP](#树形-dp)
    - [树链剖分 + 线段树区间修改查询](#树链剖分--线段树区间修改查询)
  - [字符串](#字符串)
    - [KMP](#kmp)
    - [字典树（Trie）](#字典树trie)


# 算法竞赛模板

## 杂项

### 快读

```cpp
inline ll read() {
    ll x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-' ) f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
```

### 快速输出

```cpp
inline void print(ll n) {
    if (n < 0) {
        putchar('-');
        print(-n);
        return;
    }
    if (n > 9) print(n / 10);
    putchar(n % 10 + '0');
}
```

### 二维差分

```cpp
d[x1][y1] ++; d[x2 + 1][y1] --; d[x1][y2 + 1] --; d[x2 + 1][y2 + 1] ++;
a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + d[i][j];
```

### 二维前缀和

```cpp
pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
int sum = pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
```

### 进制背包 DP

```cpp
void ACC() {
    int W, f[N], v[N], m[N];
    rep1(i, n) {
        if(m[i] * w[i] >= W) {
            forn(j, w[i], W) f[j] = max(f[j], f[j - w[i]] + v[i]);
        }
        else {
            for(int p = 1; m[i] > 0; p <<= 1) {
                int x = min(p, m[i]);
                forr(j, W, w[i] * x)
                    f[j] = max(f[j], f[j - w[i] * x] + v[i] * x);
                m[i] -= x;
            }
        }
    }
}
```

### 状态压缩 DP

```cpp
vector<int> vad, cnt_dp;
int h[N], f[10][1 << 10];
void sc_dp() {
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int x; cin >> x;
            if(x == 1) h[i] |= (1 << j);
        }
    }
    for(int i = 0; i < (1 << m); ++i) {
        if(i & (i << 1)) continue;
        vad.push_back(i);
        cnt_dp.push_back(__builtin_popcount(i));
    }
    for(int i = 0; i < vad.size(); ++i) {
        if((vad[i] & ~h[0]) == 0) {
            f[0][vad[i]] = 1;
        }
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < vad.size(); ++j) {
            int cur = vad[j];
            if(cur & ~h[i]) continue;
            for(int jj = 0; jj < vad.size(); ++jj) {
                int pre = vad[jj];
                if(pre & ~h[i - 1]) continue;
                if(pre & cur) continue;
                f[i][cur] = (f[i][cur] + f[i - 1][pre]) % MOD;
            }
        }
    }
    int ans = 0;
    for(auto && x : vad) ans = (ans + f[n - 1][x]) % MOD;
    cout << ans << el;
    return;
}
```

### 数位 DP

```cpp
void init_num() {
    for(int i = 0; i <= 9; ++i) f[1][i] = 1;
    for(int i = 2; i <= 19; ++i) {
        for(int j = 0; j <= 9; ++j) {
            for(int k = 0; k <= 9; ++k) {
                if(abs(j - k) >= 2) f[i][j] += f[i - 1][k];
            }
        }
    }
}
int rk(int n) {
    int ans = 0;
    if(n <= 0) return ans;
    vector<int> a;
    while(n) {
        a.push_back(n % 10);
        n /= 10;
    }
    reverse(a.begin(), a.end());
    int len = a.size();
    for(int i = 1; i < len; ++i) 
        for(int j = 1; j <= 9; ++j)
            ans += f[i][j];
    int pre = -1;
    for(int i = 0; i < len; ++i) {
        int cur = a[i];
        int lt = len - i - 1;
        for(int j = (i == 0 ? 1 : 0); j < cur; ++j) {
            if(pre == -1 || abs(j - pre) >= 2) 
                ans += f[lt + 1][j];
        }
        if(pre != -1 && abs(cur - pre) < 2) return ans;
        pre = cur;
    }
    return ans + 1;
}
```

## 数论

### 位运算与集合操作

```cpp
/*
全排列数组 相邻两项异或值之和最小 格雷码 i ^ (i >> 1)
输出两位小数 空位补零 cout << x << ' ' << setw(2) << setfill('0') << y << el;
*/

// 返回二进制中前导 0 的个数
int __builtin_clz(n);
// 返回二进制中末位 0 的个数
int __builtin_ctz(n);
// 返回二进制中 1 的个数 
int __builtin_popcount(n);

// 判断是否是 2 的幂
bool isMi(int x) { return x > 0 && (x & (x - 1)) == 0; }
// 获取 a 的第 b 位，最低位编号为 0
int getBit(int a, int b) { return (a >> b) & 1; }
// 将 a 的第 b 位设置为 0，最低位编号为 0
int unsetBit(int a, int b) { return a & ~(1 << b); }
// 将 a 的第 b 位设置为 1，最低位编号为 0
int setBit(int a, int b) { return a | (1 << b); }
// 将 a 的第 b 位取反，最低位编号为 0
int flapBit(int a, int b) { return a ^ (1 << b); }

// 基本位运算
#define BIT(x, i) ((x) >> (i) & 1)        // 取第 i 位，判断是 0 还是 1
#define SET(x, i) ((x) | (1ll << (i)))    // 第 i 位置 1
#define CLR(x, i) ((x) & ~(1ll << (i)))   // 第 i 位置 0
#define FLIP(x, i) ((x) ^ (1ll << (i)))   // 翻转第 i 位
#define LOWBIT(x) ((x) & -(x))            // 最低位 1
#define CLR_LOWBIT(x) ((x) & ((x) - 1))   // 去掉最低位 1
#define FULL(n) ((1ll << (n)) - 1)        // n 位全 1

// 集合操作
#define IN(x, msk) (msk >> x & 1)          // x 是否在集合 msk 中
#define ADD(x, msk) (msk | (1ll << x))     // x 加入集合
#define DEL(x, msk) (msk & ~(1ll << x))    // x 从集合中删除
#define SUB_IS(x, msk) ((msk & x) == x)    // msk 是否包含子集 x

// 枚举
#define FORSUB(i, msk) for(int i = msk; i; i = (i - 1) & msk)           // 枚举 msk 的所有非空子集
#define FORSUB2(i, msk) for(int i = msk - 1 & msk; i; i = (i - 1) & msk) // 枚举 msk 的真子集
#define FORALL(i, n) for(int i = 0; i < (1 << n); ++i)                  // 枚举全集的子集
#define FORBIT(i, msk) for(int i = __builtin_ctzll(msk); msk; msk &= msk - 1, i = __builtin_ctzll(msk)) // 枚举 msk 中为 1 的位
```

### 快速幂

```cpp
ll binpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1
    }
    return res;
}
```

### 乘法逆元（MOD为质数）

```cpp
long long inv(long long x) {
    return binpow(x, MOD - 2);
}
// 删除左边：mul = mul * inv(a[i]) % MOD;
// 加入右边：mul = mul * a[i + k] % MOD;
```

### 最大公因数

```cpp
int getGcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### 判断质数

```cpp
bool is_prime(int x) {
    if(x < 2) return false;
    for(int i = 2; i * i <= x; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}
```

### 扩展欧几里得

```cpp
int exgcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}
```

### 精确开平方

```cpp
ll get(ll n) {
    ll u = sqrt(2.0L * n);
    while (u * (u + 1) / 2 < n)
        u++;
    while (u * (u - 1) / 2 + 1 > n)
        u--;
    return u;
}
```

### 欧拉筛（线性筛）

```cpp
vector<bool> isPrime;
vector<int> primes;

vector<bool> linearSieve(int n) {
    isPrime.assign(n + 1, true);
    primes.clear();
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i <= n; i++) {
        if(isPrime[i]) primes.push_back(i);
        for(int p : primes) {
            if(i * p > n) break;
            isPrime[i * p] = false;
            if(i % p == 0) break;
        }
    }
    return isPrime;
}
```

### 欧拉筛、莫比乌斯函数、杜教筛

```cpp
/*
minP[x]  : x 的最小质因数
phi[x]   : 欧拉函数 φ(x)
mu[x]    : 莫比乌斯函数 μ(x)
sPhi[x]  : φ(1)+...+φ(x)
sMu[x]   : μ(1)+...+μ(x)
sumMu(n) : 大范围莫比乌斯前缀和
*/
unordered_map<int, int> fMu;
vector<int> minP, pri, phi, mu, sMu;
vector<long long> sPhi;

void Sieve(int n) {
    n = max<int>(n, 1);
    minP.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    sMu.assign(n + 1, 0);
    sPhi.assign(n + 1, 0);
    pri.clear();
    fMu.clear();
    phi[1] = 1;
    mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(minP[i] == 0) {
            minP[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            pri.push_back(i);
        }
        for(int p : pri) {
            if(i * p > n) break;
            minP[i * p] = p;
            if(p == minP[i]) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mu[i * p] = -mu[i];
        }
    }
    for(int i = 1; i <= n; ++i) {
        sPhi[i] = sPhi[i - 1] + phi[i];
        sMu[i] = sMu[i - 1] + mu[i];
    }
}

// 计算 M(n)=μ(1)+μ(2)+...+μ(n)
int sumMu(int n) {
    if(n <= 0) return 0;
    if(n < static_cast<int>(sMu.size())) return sMu[n];
    auto it = fMu.find(n);
    if(it != fMu.end()) return it->second;
    int ans = 1;
    for(int l = 2, r; l <= n; l = r + 1) {
        int q = n / l;
        r = n / q;
        ans -= (r - l + 1) * sumMu(q);
    }
    return fMu[n] = ans;
}

// 统计 1<=x<=n、1<=y<=m 中 gcd(x,y)=1 的有序数对
int coprimePairs(int n, int m) {
    if(n <= 0 || m <= 0) return 0;
    int ans = 0;
    for(int l = 1, r; l <= min(n, m); l = r + 1) {
        int dn = n / l;
        int dm = m / l;
        r = min(n / dn, m / dm);
        r = min(r, min(n, m));
        ans += (sumMu(r) - sumMu(l - 1)) * dn * dm;
    }
    return ans;
}

// 统计 1<=x<=n、1<=y<=m 中 gcd(x,y)=k 的有序数对
int gcdEqualsK(int n, int m, int k) {
    if(k <= 0) return 0;
    return coprimePairs(n / k, m / k);
}

// 统计 1<=x<y<=n 中 gcd(x,y)=1 的无序数对
int unorderedCoprimePairs(int n) {
    if(n <= 0) return 0;
    return (coprimePairs(n, n) - 1) / 2;
}

// 统计 1<=x<y<=n 中 gcd(x,y)=k 的无序数对
int unorderedGcdEqualsK(int n, int k) {
    if(n <= 0 || k <= 0 || k > n) return 0;
    return unorderedCoprimePairs(n / k);
}
```

### 组合数（阶乘逆元，MOD很大时适用，质数）

```cpp
ll fact[N], invfact[N];

void Init_mod() {
    fact[0] = 1;
    for(int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[N - 1] = binpow(fact[N - 1], MOD - 2);
    for(int i = N - 2; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

ll comb_mod(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fact[n] * invfact[m] % MOD * invfact[n - m] % MOD;
}
```

### 线性基

```cpp
int p[N];
void Insert(int x) {
    for(int i = 49; i >= 0; --i) {
        if((x >> i) & 1) {
            if(p[i] == 0) {
                p[i] = x;
                return;
            }
            x ^= p[i];
        }
    }
}

void XXJ() {
    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        Insert(x);
    }
    int res = 0;
    for(int i = 49; i >= 0; --i) res = max(res, res ^ p[i]);
    cout << res << el;
}
```

## 数据结构

### 并查集

```cpp
struct DSU {
    vi fa;

    //连通块的节点权值和:
    //vector<ll> sum;

    DSU(int n) {
        fa.resize(n + 1);
        for (int i = 0; i <= n; ++i) fa[i] = i;

        // for (int i = 0; i <= n; ++i) sum[i] = a[i]; // 维护节点数量: sum[i] = 1
    }
    int find(int u) {
        if(fa[u] == u) return u;
        return fa[u] = find(fa[u]);
    }
    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return;
        fa[rv] = ru;
        //sum[ru] += sum[rv];
    }
    //ll getsum(int u){ return sum[find(u)]; }
};
```

### ST表

```cpp
int n, a[N], st[N][LOG], lg[N];

void build_st() {
    lg[1] = 0;
    for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= n; ++i) st[i][0] = a[i];
    for(int j = 1; j <= lg[n]; ++j) {
        for(int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}

int query_gcd(int l, int r) {
    int len = r - l + 1;
    int k = lg[len];
    return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
```

### 离散化

```cpp
vector<int> disc(const vector<int> &a) {
    vector<int> b = a;
    vector<int> tmp = a;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for(int i = 0; i < b.size(); ++i) 
        b[i] = lower_bound(tmp.begin(), tmp.end(), b[i]) - tmp.begin() + 1;
    return b;
}
```

### 前缀和正序对

```cpp
int SeOrd() {
    int b[N], c[N];
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
        b[i] = pre[i];
    }
    sort(b, b + n + 1);
    m = unique(b, b + n + 1) - b;
    for(int i = 0; i <= n; ++i)
        c[i] = lower_bound(b, b + m, pre[i]) - b + 1;
    add(c[0], 1);
    ll cnt = 0;
    for(int i = 1; i <= n; ++i) {
        cnt += preSum(c[i] - 1);
        add(c[i], 1);
    }
    return cnt;
}
```

### 逆序对

```cpp
int Opord() {
    int b[N], c[N];
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; ++i)
        c[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
    ll cnt = 0;
    for(int i = 1; i <= n; ++i) {
        cnt += (i - 1) - preSum(c[i]);
        add(c[i], 1);
    }
    return cnt;
}
```

### 树状数组

```cpp
int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k) {
    while(x <= n) {
        a[x] += k;
        x += lowbit(x);
    }
}

int preSum(int x) {
    ll res = 0;
    while(x) {
        res += a[x];
        x -= lowbit(x);
    }
    return res;
}
```

### 区间乘、区间加、区间赋值、最值查询、区间查询（Lazy线段树）

```cpp
struct node {
    int L, R;
    ll mdf, add, mul, mx, sum;
} tree[N << 2];

void build(int k, int l, int r) {
    tree[k].L = l;
    tree[k].R = r;
    tree[k].mdf = -1;
    tree[k].mul = 1;
    tree[k].add = 0;
    if(l == r) {
        tree[k].mx = tree[k].sum = a[l];
        return;
    }
    int mid, lc, rc;
    mid = (l + r) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

void lazy_mdf(int k, ll v) {
    int len = tree[k].R - tree[k].L + 1;
    tree[k].mx = v;
    tree[k].sum = len * v;
    tree[k].mdf = v;
    tree[k].mul = 1;
    tree[k].add = 0;
}

void lazy_mul(int k, ll v) {
    tree[k].mx *= v;
    tree[k].sum *= v;
    if(tree[k].mdf != -1) tree[k].mdf *= v;
    else {
        tree[k].mul *= v;
        tree[k].add *= v;
    }
}

void lazy_add(int k, ll v) {
    int len = tree[k].R - tree[k].L + 1;
    tree[k].mx += v;
    tree[k].sum += len * v;
    if(tree[k].mdf != -1) tree[k].mdf += v;
    else tree[k].add += v;
}

void pushdown(int k) {
    if(tree[k].mdf != -1) {
        lazy_mdf(k << 1, tree[k].mdf);
        lazy_mdf(k << 1 | 1, tree[k].mdf);
        tree[k].mdf = -1;
    }
    if(tree[k].mul != 1) {
        lazy_mul(k << 1, tree[k].mul);
        lazy_mul(k << 1 | 1, tree[k].mul);
        tree[k].mul = 1;
    }
    if(tree[k].add != 0) {
        lazy_add(k << 1, tree[k].add);
        lazy_add(k << 1 | 1, tree[k].add);
        tree[k].add = 0;
    }
}

void update_mul(int k, int l, int r, ll v) {
    if(tree[k].L >= l && tree[k].R <= r) return lazy_mul(k, v);
    pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].L + tree[k].R) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    if(l <= mid) update_mul(lc, l, r, v);
    if(r > mid) update_mul(rc, l, r, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

void update_add(int k, int l, int r, ll v) {
    if(tree[k].L >= l && tree[k].R <= r) return lazy_add(k, v);
    pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].L + tree[k].R) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    if(l <= mid) update_add(lc, l, r, v);
    if(r > mid) update_add(rc, l, r, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

void update_mdf(int k, int l, int r, ll v) {
    if(tree[k].L >= l && tree[k].R <= r) return lazy_mdf(k, v);
    pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].L + tree[k].R) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    if(l <= mid) update_mdf(lc, l, r, v);
    if(r > mid) update_mdf(rc, l, r, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

ll query_mx(int k, int l, int r) {
    if(tree[k].L >= l && tree[k].R <= r) return tree[k].mx;
    pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].L + tree[k].R) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    ll res = LLONG_MIN;
    if(l <= mid) res = max(res, query_mx(lc, l, r));
    if(r > mid) res = max(res, query_mx(rc, l, r));
    return res;
}

ll query_sum(int k, int l, int r) {
    if(tree[k].L >= l && tree[k].R <= r) return tree[k].sum;
    pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].L + tree[k].R) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    ll res = 0;
    if(l <= mid) res += query_sum(lc, l, r);
    if(r > mid) res += query_sum(rc, l, r);
    return res;
}
```

### 区间加等差数列 + 单点查询（线段树）

```cpp
struct Node {
    int left, right;
    ll val, k, d;
} tree_ap[N << 2];

void build(int k, int l, int r) {
    tree_ap[k].left = l;
    tree_ap[k].right = r;
    tree_ap[k].k = 0;
    tree_ap[k].d = 0;
    if(l == r) {
        tree_ap[k].val = a[l]; 
        return;
    }
    int mid, lc, rc;
    mid = (l + r) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void pushdown(int k) {
    int mid, lc, rc;
    mid = (tree_ap[k].left + tree_ap[k].right) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    int len_left = mid - tree_ap[k].left + 1;
    tree_ap[lc].k += tree_ap[k].k;
    tree_ap[lc].d += tree_ap[k].d;
    if(tree_ap[lc].left == tree_ap[lc].right) tree_ap[lc].val += tree_ap[k].k;
    tree_ap[rc].k += tree_ap[k].k + len_left * tree_ap[k].d;
    tree_ap[rc].d += tree_ap[k].d;
    if(tree_ap[rc].left == tree_ap[rc].right)
        tree_ap[rc].val += tree_ap[k].k + len_left * tree_ap[k].d;
    tree_ap[k].k = 0;
    tree_ap[k].d = 0;
}

void update(int k, int l, int r, ll K, ll D) {
    if(tree_ap[k].left >= l && tree_ap[k].right <= r) {
        int len = tree_ap[k].left - l;
        ll cur_k = K + len * D;
        tree_ap[k].k += cur_k;
        tree_ap[k].d += D;
        if(tree_ap[k].left == tree_ap[k].right) tree_ap[k].val += cur_k;
        return;
    }
    if(tree_ap[k].k != 0 || tree_ap[k].d != 0) pushdown(k);
    int mid, lc, rc;
    mid = (tree_ap[k].left + tree_ap[k].right) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    if(l <= mid) update(lc, l, r, K, D);
    if(r > mid) update(rc, l, r, K, D);
}

ll query(int k, int p) {
    if(tree_ap[k].left == tree_ap[k].right && tree_ap[k].left == p) 
        return tree_ap[k].val;
    if(tree_ap[k].k != 0 || tree_ap[k].d != 0) pushdown(k);
    int mid, lc, rc;
    mid = (tree_ap[k].left + tree_ap[k].right) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    ll res = 0;
    if(p <= mid) res += query(lc, p);
    if(p > mid) res += query(rc, p);
    return res;
}
```

### 莫队

```cpp
const int N = 1e6 + 10;
int n, m, k, res, block;
int a[N], cnt[N], ans[N];

struct Q {
    int l, r, id, pos;
    bool operator<(const Q& other) const {
        if(pos != other.pos) return pos < other.pos;
        return (pos & 1) ? (r < other.r) : (r > other.r);
    }
} q_mo[N];

inline void add(int x) {
    res += cnt[a[x]];
    cnt[a[x]]++;
}

inline void del(int x) {
    cnt[a[x]]--;
    res -= cnt[a[x]];
}

void Mo() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    block = n / sqrt(m * 2 / 3 + 1) + 1;
    for(int i = 0; i < m; ++i) {
        q_mo[i].l = read(), q_mo[i].r = read();
        q_mo[i].id = i;
        q_mo[i].pos = q_mo[i].l / block;
    }
    sort(q_mo, q_mo + m);
    int L = 1, R = 0;
    res = 0;
    for(int i = 0; i < m; ++i) {
        int tL = q_mo[i].l;
        int tR = q_mo[i].r;
        while (L > tL) add(--L);
        while (R < tR) add(++R);
        while (L < tL) del(L++);
        while (R > tR) del(R--);
        ans[q_mo[i].id] = res;
    }
    for(int i = 0; i < m; ++i) {
        print(ans[i]);
        putchar('\n');
    }
}
```

## 图论

### 拓扑排序

```cpp
vector<int> gr[N];

vector<int> topo(int n, int m, vector<pair<int,int>>& edges) {
    vector<int> idg(n + 1, 0);
    for(int i = 1; i <= n; ++i) gr[i].clear();
    for(auto& e : edges) {
        int x = e.first, y = e.second;
        gr[x].push_back(y);
        idg[y]++;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= n; ++i) {
        if(idg[i] == 0) pq.push(i);
    }
    vector<int> ans;
    while(!pq.empty()) {
        int u = pq.top(); pq.pop();
        ans.push_back(u);
        for(int v : gr[u]) {
            idg[v]--;
            if(idg[v] == 0) pq.push(v);
        }
    }
    return ans;
}
```

### Dijkstra 单源最短路（朴素）

```cpp
int edge[N][N], dis[N], pre[N]; // 初始化 edge 和 dis 是 0x3f，pre 是 -1 (edge[i][i] = 0)
bool vis[N];

void dijkstra(int source) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[source] = 0;
    while(true) {
        int minVex = 0;
        for(int i = 1; i <= n; ++i) {
            if(!vis[i] && dis[minVex] > dis[i]) minVex = i;
        }
        if(minVex == 0) break;
        vis[minVex] = 1;
        for(int i = 1; i <= n; ++i) {
            if(dis[i] > dis[minVex] + edge[minVex][i]) {
                dis[i] = dis[minVex] + edge[minVex][i];
                pre[i] = minVex;
            }
        }
    }
}

// 路径输出
void output(int x) {
    if(x == -1) return;
    output(pre[x]);
    cout << x << ' ';
}
```

### Dijkstra（邻接表 + 优先队列优化）

```cpp
struct Edge {
    int end, w;
};
vector<Edge> g[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> qq;

void dijkstra(int sta) {
    memset(dis, 0x3f, sizeof(dis));
    dis[sta] = 0;
    qq.push(make_pair(dis[sta], sta));
    while(!qq.empty()) {
        pair<int, int> cur = qq.top();
        qq.pop();
        int Dis = cur.first, idx = cur.second;
        if(Dis > dis[idx]) continue;
        for(int i = 0; i < g[idx].size(); ++i) {
            int v = g[idx][i].end, w = g[idx][i].w;
            if(dis[v] > dis[idx] + w) {
                dis[v] = dis[idx] + w;
                qq.push(make_pair(dis[v], v));
            }
        }
    }
}
```

### Floyd 多源最短路

```cpp
int f_dis[N][N], f_pre[N][N], f_edge[N][N];

void build_floyd() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i == j) f_edge[i][j] = 0;
            else f_edge[i][j] = INT_MAX;
        }
    }
}

void floyd() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            f_dis[i][j] = f_edge[i][j];
            if(f_edge[i][j] != INT_MAX && i != j) f_pre[i][j] = i;
            else f_pre[i][j] = -1;
        }
    }
    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(f_dis[i][k] != INT_MAX && f_dis[k][j] != INT_MAX && 
                   f_dis[i][j] > f_dis[i][k] + f_dis[k][j]) {
                    f_dis[i][j] = f_dis[i][k] + f_dis[k][j];
                    f_pre[i][j] = f_pre[k][j];
                }
            }
        }
    }
}

void output_floyd(int x, int y) {
    if(f_pre[x][y] != -1) output_floyd(x, f_pre[x][y]);
    cout << y << ' ';
}
// 输入时加 edge[u][v] = min(edge[u][v], w); 若无向再加上 edge[v][u] = min(edge[v][u], w);
// 传递闭包：f_dis[i][j] = f_dis[i][j] | f_dis[i][k] & f_dis[k][j];
```

### Bellman-Ford

```cpp
int m;
struct edge {
    int u, v, w;
} e[N * N];

int BellmanFord(int source) {
    memset(dis, INT_MIN, sizeof(dis));
    dis[source] = 0;
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int u = e[j].u, v = e[j].v, w = e[j].w;
            dis[v] = min(dis[v], dis[u] + w);
        }
    }
    for(int j = 1; j <= m; ++j) {
        int u = e[j].u, v = e[j].v, w = e[j].w;
        if(dis[v] > dis[u] + w) return -1;
    }
    return 0;
}
```

### 最小生成树 Prim

```cpp
int prim(int source) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    dis[source] = 0;
    int cnt = 0, ans = 0;
    while(true) {
        int minVex = 0;
        for(int i = 1; i <= n; ++i) {
            if(vis[i] == false && dis[minVex] > dis[i]) minVex = i;
        }
        if(minVex == 0) break;
        cnt++;
        ans += dis[minVex];
        vis[minVex] = true;
        for(int i = 1; i <= n; ++i) {
            if(vis[i] == false && dis[i] > edge[minVex][i]) {
                dis[i] = edge[minVex][i];
                pre[i] = minVex;
            }
        }
    }
    if(cnt != n) return -1;
    else return ans;
}
```

### 最小生成树 Kruskal

```cpp
struct Edge { int u, v, w; };
vector<Edge> edges;
sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
DSU dsu(n);
long long ans = 0, cnt = 0;
for (auto [u,v,w] : edges) {
    if (dsu.find(u) != dsu.find(v)) {
        dsu.unite(u, v);
        ans += w;
        cnt++;
        if (cnt == n-1) break;
    }
}
```

### SPFA 负环

```cpp
struct edge_spfa {
    int v, w, nxt;
} e_spfa[N * N];
int n, m, sta, cnt_spfa, dis[N], head[N], inc[N]; // 主函数 head 初始化为 -1，vis 初始化为 0
bool vis[N];
queue<int> q;

void add_e(int u, int v, int w) {
    cnt_spfa++;
    e_spfa[cnt_spfa].v = v;
    e_spfa[cnt_spfa].w = w;
    e_spfa[cnt_spfa].nxt = head[u];
    head[u] = cnt_spfa;
}

int spfa(int sta) {
    memset(dis, 0x3f, sizeof dis);
    memset(inc, 0, sizeof inc);
    memset(vis, 0, sizeof vis);
    while(!q.empty()) q.pop();
    dis[sta] = 0;
    q.push(sta);
    vis[sta] = 1; inc[sta]++;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i != -1; i = e_spfa[i].nxt) {
            int v = e_spfa[i].v;
            if(dis[v] > dis[u] + e_spfa[i].w) {
                dis[v] = dis[u] + e_spfa[i].w;
                if(!vis[v]) {
                    if(++inc[v] > n) return -1;
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return 0;
}
// 若为差分约束，主函数添加 for(int i = 1; i <= n; ++i) add_e(0, i, 0);
```

### LCA 倍增法

```cpp
int k;
vector<int> adj[N];
int pa[N][LOG], dep[N], wid[N];

void dfs(int u, int f) {
    pa[u][0] = f;
    wid[dep[u]]++; // width
    for(int v : adj[u]) {
        if(v != f) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
}

void st_create() {
    k = log2(n);
    for(int j = 1; j <= k; ++j) {
        for(int i = 1; i <= n; ++i) pa[i][j] = pa[pa[i][j - 1]][j - 1];
    }
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = k; i >= 0; --i) {
        if(dep[u] - (1 << i) >= dep[v]) u = pa[u][i];
    }
    if(u == v) return u;
    for(int i = k; i >= 0; --i) {
        if(pa[u][i] != pa[v][i]) {
            u = pa[u][i]; v = pa[v][i];
        }
    }
    return pa[u][0];
}
```

### 树的直径

```cpp
int maX;

void dfs(int u, int f) {
    for(auto &v : adj[u]) {
        if(v != f) continue;
        dep[v] = dep[u] + 1;
        if(dep[v] > dep[maX]) maX = v;
        dfs(v, u);
    }
}
```

### 欧拉回路（Hierholzer）

```cpp
multiset<int> g_E[N];
int idg[N], udg[N];
vector<int> path;
int n, m, sta = 1e9;

void dfs_E(int u) {
    while(!g_E[u].empty()) {
        int v = *g_E[u].begin();
        g_E[u].erase(g_E[u].begin());
        g_E[v].erase(g_E[v].find(u)); // 无向边才写
        dfs_E(v);
        path.push_back(v);
    }
}

void Hierholzer() {
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        n = max(n, max(u, v));
        sta = min(sta, min(u, v));
        g_E[u].insert(v); g_E[v].insert(u);
        idg[u]++; idg[v]++;
    }
    for(int i = 1; i <= n; ++i)
        if(idg[i] & 1) {
            sta = i;
            break;
        }
    dfs_E(sta);
    path.push_back(sta);
    reverse(path.begin(), path.end());
    for(int x : path) cout << x << '\n';
}
```

### 欧拉路（有向图）

```cpp
void Eulerian() {
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        sta = min(sta, min(u, v));
        g_E[u].insert(v);
        idg[v]++; udg[u]++;
    }
    int r1 = 0, r2 = 0;
    for(int i = 1; i <= n; ++i) {
        if(udg[i] - 1 == idg[i]) {
            sta = i; r1++;
        }
        else if(idg[i] - 1 == udg[i]) r2++;
        else if(idg[i] != udg[i]) {
            cout << "No" << el;
            return;
        }
    }
    if(!((r1 == 0 && r2 == 0) || (r1 == 1 && r2 == 1))) {
        cout << "No" << el;
        return;
    }
    dfs(sta);
    path.push_back(sta);
    reverse(path.begin(), path.end());
    if(path.size() != m + 1) {
        cout << "No" << el;
        return;
    }
    for(int x : path) cout << x << el;
}
```

### 二分图判定

```cpp
vector<int> g_bip[N];
vector<int> col, vis;
int n, m;

bool dfs_bip(int u) {
    vis[u] = 1;
    for(int v : g_bip[u]) {
        if(vis[v]) {
            if(col[u] == col[v]) return 0;
        }
        else {
            col[v] = col[u] ^ 1;
            if(!dfs_bip(v)) return 0;
        }
    }
    return 1;
}

bool check_bip() {
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            col[i] = 0;
            if(!dfs_bip(i)) return 0;
        }
    }
    return 1;
}
```

### 匈牙利算法

```cpp
vector<int> adj_xyl[N];
int mtc[N];
bool vis[N];

bool dfs(int u) {
    for(int v : adj_xyl[u]) {
        if(vis[v]) continue;
        vis[v] = 1;
        if(mtc[v] == -1 || dfs(mtc[v])) {
            mtc[v] = u;
            return 1;
        }
    }
    return 0;
}

int hungarian(int n) {
    int ans = 0;
    memset(mtc, -1, sizeof mtc);
    for(int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        if(dfs(i)) ans++;
        // else break; 在顺序匹配要加上
    }
    return ans;
}
```

### 树形 DP

```cpp
int f_t[N][2], w_t[N];
vector<int> g_t[N];

void dfs_t(int u, int fa) {
    f_t[u][0] = 0;
    f_t[u][1] = w_t[u];
    for(int v : g_t[u]) {
        if(v == fa) continue;
        dfs_t(v, u);
        f_t[u][0] += max(f_t[v][0], f_t[v][1]);
        f_t[u][1] += f_t[v][0];
    }
}
```

### 树链剖分 + 线段树区间修改查询

```cpp
int w[N];
vector<int> g_tr[N];
int fa[N], dep[N], sz[N], son[N], top[N], id[N], nw[N];
int num, n, m, r, MOD;

void dfs1(int u, int pa) {
    fa[u] = pa;
    dep[u] = dep[pa] + 1;
    sz[u] = 1;
    for(int v : g_tr[u]) {
        if(v == pa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    id[u] = ++num;
    nw[num] = w[u] % MOD;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int v : g_tr[u]) {
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

struct node {
    int left, right;
    ll add, sum, lz;
} tr[N << 2];

void build(int k, int l, int r) {
    tr[k].left = l;
    tr[k].right = r;
    tr[k].add = 0;
    tr[k].sum = 0;
    tr[k].lz = 0;
    if(l == r) {
        tr[k].sum = nw[l];
        return;
    }
    int mid, lc, rc;
    mid = (l + r) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tr[k].sum = (tr[lc].sum + tr[rc].sum) % MOD;
}

void lazy(int k, ll v) {
    int len = tr[k].right - tr[k].left + 1;
    tr[k].sum = (tr[k].sum + v * len) % MOD;
    tr[k].lz = (tr[k].lz + v) % MOD;
}

void pushdown(int k) {
    if(tr[k].lz == 0) return;
    lazy(k << 1, tr[k].lz);
    lazy(k << 1 | 1, tr[k].lz);
    tr[k].lz = 0;
}

void update(int k, int l, int r, ll v) {
    if(tr[k].left >= l && tr[k].right <= r) return lazy(k, v);
    pushdown(k);
    int mid, lc, rc;
    mid = (tr[k].left + tr[k].right) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    if(l <= mid) update(lc, l, r, v);
    if(r > mid) update(rc, l, r, v);
    tr[k].sum = (tr[lc].sum + tr[rc].sum) % MOD;
}

void update_path(int u, int v, int x) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], x);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], x);
}

ll query(int k, int l, int r) {
    if(tr[k].left >= l && tr[k].right <= r) return tr[k].sum;
    pushdown(k);
    int mid, lc, rc;
    mid = (tr[k].left + tr[k].right) >> 1;
    lc = k << 1, rc = k << 1 | 1;
    ll res = 0;
    if(l <= mid) res = (res + query(lc, l, r)) % MOD;
    if(r > mid) res = (res + query(rc, l, r)) % MOD;
    return res % MOD;
}

ll query_path(int u, int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res = (res + query(1, id[top[u]], id[u])) % MOD;
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    res = (res + query(1, id[v], id[u])) % MOD;
    return res % MOD;
}
```

## 字符串

### KMP

```cpp
int kmp(int n, int m, string s1, string s2, int nxt[N]) {
    for(int i = 2, j = 0; i <= n; ++i) {
        while(j > 0 && s2[i] != s2[j + 1]) j = nxt[j];
        if(s2[i] == s2[j + 1]) j++;
        nxt[i] = j;
    }
    for(int i = 1, j = 0; i <= m; ++i) {
        while(j > 0 && s1[i] != s2[j + 1]) j = nxt[j];
        if(s1[i] == s2[j + 1]) j++;
        if(j == n) {
            cout << i - j + 1 << '\n';
            j = nxt[j];
        }
    }
}
```

### 字典树（Trie）

```cpp
int trie[N][26], tot = 0;
int cnt[N];

void insert(const string &s) {
    int u = 0;
    for(char ch : s) {
        int c = ch - 'a';
        if(!trie[u][c]) trie[u][c] = ++tot;
        u = trie[u][c];
    }
    cnt[u]++;
}

int query(const string &s) {
    int u = 0;
    for(char ch : s) {
        int c = ch - 'a';
        if(!trie[u][c]) return 0;
        u = trie[u][c];
    }
    return cnt[u];
}

bool staWith(const string &s) {
    int u = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!trie[u][c]) return false;
        u = trie[u][c];
    }
    return true;
}
```