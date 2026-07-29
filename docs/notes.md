- [算法竞赛常用模板速查](#算法竞赛常用模板速查)
  - [模板](#模板)
  - [示例](#示例)
  - [二分答案](#二分答案)
  - [前缀和与差分](#前缀和与差分)
    - [1. 前缀和](#1-前缀和)
    - [2. 二维前缀和](#2-二维前缀和)
    - [3. 一维差分](#3-一维差分)
  - [位运算常用](#位运算常用)
  - [离散化](#离散化)
  - [数据结构](#数据结构)
    - [并查集](#并查集)
    - [ST表](#st表)
    - [单调栈（下一个更大元素）](#单调栈下一个更大元素)
    - [树状数组](#树状数组)
  - [图论](#图论)
    - [DFS](#dfs)
    - [BFS](#bfs)
    - [拓扑排序(Kahn)](#拓扑排序kahn)
    - [Dijkstra](#dijkstra)
    - [Kruskal](#kruskal)
    - [LCA 倍增](#lca-倍增)
  - [动态规划](#动态规划)
    - [1. 0‑1 背包](#1-01-背包)
    - [2. 完全背包](#2-完全背包)
    - [3. 多重背包](#3-多重背包)
    - [4. 分组背包（每组最多选一个）](#4-分组背包每组最多选一个)
    - [5. LIS（最长上升子序列，O(n log n)）](#5-lis最长上升子序列on-log-n)
    - [6. 最大子段和（贪心 / DP）](#6-最大子段和贪心--dp)
  - [数论基础](#数论基础)
    - [1. gcd](#1-gcd)
    - [2. 快速幂](#2-快速幂)
  - [C++ STL使用](#c-stl使用)
    - [STL容器](#stl容器)
      - [通用容器方法](#通用容器方法)
      - [1. `vector`](#1-vector)
      - [2. `deque`（双端队列）](#2-deque双端队列)
      - [4. `string`（字符串）](#4-string字符串)
      - [5. `set`（有序集合）](#5-set有序集合)
      - [6. `map`（有序映射）](#6-map有序映射)
      - [7. `unordered_set` / `unordered_map`（哈希集合/映射）](#7-unordered_set--unordered_map哈希集合映射)
      - [8. 容器适配器](#8-容器适配器)
      - [`stack`（栈）](#stack栈)
      - [`queue`（队列）](#queue队列)
      - [`priority_queue`（优先队列，默认最大堆）](#priority_queue优先队列默认最大堆)
    - [STL函数](#stl函数)
      - [1. 排序与查找](#1-排序与查找)
      - [2. 修改与操作](#2-修改与操作)
      - [3. 数值算法](#3-数值算法)


# 算法竞赛常用模板速查

本文件的代码会持续维护。  
> 暂未完工。

## 模板
标准版, 最大化可读性。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

void solve()
{

}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    return 0;
}
```
---
完全版，加入了很多宏。
```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int>>;

#define all(x) (x).begin(), (x).end()
#define pb push_back

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

void solve()
{

}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    return 0;
}
```

## 示例

```cpp
vector<int> v1;                         // 空vector
vector<int> v2(10, 5);                  // 10个5
vector<int> v3{1, 2, 3, 4};             // 列表初始化

map<string, int> mp;                    // 空map
mp["one"] = 1;                          // 插入

// vector 添加/删除
v1.push_back(100);
v1.pop_back();
v1.insert(v1.begin(), 99);
v1.erase(v1.begin());

// 遍历
for (int x : v1) cout << x << " ";
for (auto it = v1.begin(); it != v1.end(); ++it) cout << *it << " ";

// map 查找
if (mp.find("one") != mp.end()) {
    cout << mp["one"];          // 使用[]再次访问
}

vector<int> a = {5, 2, 8, 1, 9};
a.erase(unique(a.begin(), a.end()), a.end());     // 去重
reverse(a.begin(), a.end());                      // 反转
int sum = accumulate(a.begin(), a.end(), 0);      // 累加
auto it = find(a.begin(), a.end(), 8);            // 查找
if (it != a.end()) cout << *it;

//排序
sort(a.begin(), a.end());                     // 升序
sort(a.begin(), a.end(), greater<int>());     // 降序
sort(a.begin(), a.end(), [](int x, int y){ return x > y; });

//二分查找
int pos = lower_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 >= x
int pos = upper_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 > x
bool exist = binary_search(a.begin(), a.end(), x);
```


## 二分答案

```cpp
// 判断是否可行
bool check(int x){...}

int l = 0, r = INF;
while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) l = mid + 1;
    else r = mid - 1;
}
```
最大可行值为 `r` , 最小可行值为 `l`.  


## 前缀和与差分
本部分下标以1为起点。

### 1. 前缀和
用于静态下的区间和查询。
区间[l, r]和 = pref[r] - pref[l-1]
```cpp
vector<int> nums(n+1);
vector<int> pref(n+1);
for (int i=1; i<=n; i++){
    pref[i] = pref[i-1] + nums[i];
}
```
### 2. 二维前缀和
`(x1,y1)` 左上角, `(x2,y2)` 右下角的矩阵和 =   
`pref[x2][y2] - pref[x1-1][y2] - pref[x2][y1-1] + pref[x1-1][y1-1]`
```cpp
vector<vector<int>> pref(n+1, vector<int>(m+1));
for (int i=1; i<=n; i++)
    for (int j=1; j<=m; j++)
        pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + pref[i][j];
```
### 3. 一维差分
用于区间加，单点查.  
对差分数组执行前缀和得到数据.
```cpp
vector<int> nums(n+1);
vector<int> diff(n+1);
for (int i=1; i<=n; i++)
    diff[i] = nums[i] - nums[i-1];

// 区间[l, r]的数据 += x
void add(int l, int r, int x) {
    d[l] += x;
    if(r < n)
        d[r+1] -= x;
}
```

## 位运算常用
```cpp
(x >> k) & 1         // 取出第 k 位
x | (1 << k)         // 第 k 位置 1
x & ~(1 << k)        // 第 k 位置 0
x & -x               // lowbit
x & (x-1) == 0       // 判断是否为 2 的幂（x>0）
```

## 离散化
```cpp
vector<int> nums(n);
vector<int> temp(nums);
sort(temp.begin(), temp.end());
temp.erase(unique(temp.begin(), temp.end()), temp.end());

// 查询原值 x 对应的下标
int idx = lower_bound(temp.begin(), temp.end(), x) - temp.begin();
```

---

## 数据结构

### 并查集
```cpp
struct DSU {
    vi fa;

    //连通块的节点权值和:
    //vector<int> sum;

    DSU(int n) {
        fa.resize(n + 1);
        for (int i = 0; i <= n; ++i) fa[i] = i;

        // 维护大小则a[i] = 1
        // for (int i = 0; i <= n; ++i) sum[i] = a[i];
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
    //int getsum(int u){
    //     return sum[find(u)];
    //}
};
```

### ST表
本代码用于求区间最大值。
```cpp
int LOG = log2(n) + 2;
vector<vector<int>> f(n + 1, vector<int>(LOG));
for (int i = 1; i <= n; i++)
{
    cin >> f[i][0];
}
for (int j = 1; j < LOG; j++)
{
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
    {
        f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    }
}

// 查询[l,r]区间最大值
int s = log2(r - l + 1);
cout << max(f[l][s], f[r - (1 << s) + 1][s]) << '\n';
```

### 单调栈（下一个更大元素）
```cpp
vector<int> nums;
vector<int> next(n, -1);
stack<int> st;
for (int i=0; i<n; ++i) {
    while (!st.empty() && nums[st.top()] < nums[i]) {
        next[st.top()] = i;
        st.pop();
    }
    st.push(i);
}
```

### 树状数组
用于单点修改, 区间查询
```cpp
vector<int> bit(n+1, 0);

void add(int i, int x) { // a[i] += x
    while(i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}
int pre_sum(int i) { // 前缀和
    int res=0;
    while(i > 0) {
        res += bit[i];
        i -= i & -i;
    }
    return res;
}

// 构造
for (int i = 1; i <= n; i++) { 
    add(i, a[i]);   // a[] 数据
}

// 区间修改 + 单点查询（差分树状数组）
// 区间 [l,r] 加 c : add(l, c); add(r+1, -c);
// 单点查询: sum(x)
```


## 图论

### DFS
```cpp
vector<vector<int>> g;
vector<char> vis;
void dfs(int u) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v])
            dfs(v);
}
```

### BFS
求深度。
```cpp
queue<int> q;
vector<int> dist(n+1, -1);
dist[1]=0;
q.push(1);
while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u])
        if (dist[v]==-1) {
            dist[v]=dist[u]+1;
            q.push(v);
        }
}
```

### 拓扑排序(Kahn)

```cpp
vector<vector<int>> g(n+1);
vector<int> indeg(n+1, 0);

// 初始化入度
for(int i = 1; i <= n; i++;){
    for(int v : g[i]){
        indeg[v]++;
    }
}

queue<int> q;
for (int i=1; i<=n; i++){
    if (indeg[i]==0)
        q.push(i);
}

vector<int> topo;
while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.push_back(u);
    for (int v : g[u]) {
        indeg[v]--;
        if (indeg[v]==0)
            q.push(v);
    }
}
```
topo.size() != n 则存在环. 

### Dijkstra

单源最短路径
```cpp

vector<vector<pii>> g(n+1);
vll dist(n+1, INF);

// 起点k
dist[k] = 0;
priority_queue<pii, vector<pii>, greater<pii>> pq;
pq.push({k, 0});
while (!pq.empty()) {
    auto [d,u] = pq.top(); pq.pop();
    if (d != dist[u]) continue;
    for (auto [v,w] : g[u]) {
        if (dist[v] > d + w) {
            dist[v] = d + w;
            pq.push({dist[v], v});
        }
    }
}
```

### Kruskal
参看[并查集](#并查集). 
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
// cnt == n-1 则成功
```

---

### LCA 倍增
> 未验证
```cpp
const int LOG = log2(n)+1;

// DFS 预处理
void dfs(int u, vector<vector<int>>& g, vector<int>& depth, vector<vector<int>>& f) {
    for (int v : g[u]) {
        if (depth[v] != 0) {
            f[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(v, g, depth, f);
        }
    }
}

// LCA 查询
int lca(int u, int v, vector<int>& depth, vector<vector<int>>& f) {
    if (depth[u] < depth[v])
        swap(u, v);

    for (int j = LOG-1; j >= 0; j--) {
        if (depth[f[u][j]] >= depth[v]) {
            u = f[u][j];
        }
    }
    if (u == v)
        return u;

    for (int j = LOG-1; j >= 0; j--) {
        if (f[u][j] != f[v][j]) {
            u = f[u][j];
            v = f[v][j];
        }
    }
    return f[u][0];
}

vector<int> depth(n + 1, 0);//节点深度
vector<vector<int>> f(n + 1, vector<int>(LOG, 0));
//f[i][j] : 节点 i 向上跳 2^j 步到达的节点

// 设 1 为根节点.
depth[1] = 1;
dfs(1, g, dep, f);

// 构建倍增表
for (int j = 1; j < LOG; ++j) {
    for (int i = 1; i <= n; ++i) {
        f[i][j] = f[f[i][j-1]][j-1];
    }
}

```

## 动态规划

### 1. 0‑1 背包
```cpp
vector<int> dp(C+1, 0); // C 为容量
for (int i=1; i<=n; ++i)
    for (int j=C; j>=w[i]; --j)
        dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
```

### 2. 完全背包
```cpp
for (int i=1; i<=n; ++i)
    for (int j=w[i]; j<=C; ++j)
        dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
```

### 3. 多重背包
```cpp
// 将数量 k 拆分为 1,2,4,..., 剩余部分，转为 0‑1 背包
vector<pii> items;// w, v

for (int i = 0; i < n; i++) {
    int k = 1;
    int w,v,m;
    cin >> w >> v >> m;//或用struct存
    while (m >= k) {
        items.push_back({w*k, v*k});
        m -= k;
        k *= 2;
    }
    if (m) {
        items.push_back({w*m, v*m});
    }
}
// 然后对 cnt 个物品做 0‑1 背包
```

### 4. 分组背包（每组最多选一个）
```cpp
vector<vector<pii>> groups;//pii: w, val;
vector<ll> dp(c+1, 0);
for(auto & group : groups){// 循环每组
    for(int j = c; j >= 0; j--){ // 容量倒序
        for(auto & pr: group){// 组内物品
            int w = pr.first, v = pr.second;
            if(w <= j){
                dp[j] = max(dp[j], dp[j-w] + v);
            }
        }
    }
}
```

### 5. LIS（最长上升子序列，O(n log n)）
```cpp
vector<int> tails; // tails[i] 长度为 i+1 的上升子序列的末尾最小值
for (int x : a) {
    auto it = lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end())
        tails.push_back(x);
    else
        *it = x;
}
int ans = tails.size();
```

### 6. 最大子段和（贪心 / DP）
```cpp
int cur = 0, mx = -1e9;
for (int i=0; i<n; i++) {
    cur = max(a[i], cur + a[i]);
    mx = max(mx, cur);
}
```

---

## 数论基础

### 1. gcd
```cpp
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b);}
// 最小公倍数 lcm = a / gcd(a,b) * b
```

### 2. 快速幂
下面的算法求`a ^ b % p`的结果。

x 的逆元为 `x ^ (p-2) % p`
```cpp
long long qpow(long long a, long long b, long long p) {
    long long res = 1;
    while (b > 0) {
        if (b & 1){
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
```


## C++ STL使用

### STL容器

#### 通用容器方法

以下方法几乎所有容器都支持。

| 方法签名                    | 说明           |
| --------------------------- | -------------- |
| `size_t size() const`       | 元素个数       |
| `bool empty() const`        | 是否为空       |
| `void clear()`              | 清空所有元素   |
| `iterator begin()`          | 首迭代器       |
| `iterator end()`            | 尾后迭代器     |
| `reverse_iterator rbegin()` | 反向首迭代器   |
| `reverse_iterator rend()`   | 反向尾后迭代器 |

#### 1. `vector`

| 方法签名                                        | 说明                            |
| ----------------------------------------------- | ------------------------------- |
| `void push_back(const T& val)`                  | 尾部添加元素                    |
| `void pop_back()`                               | 删除尾部元素                    |
| `iterator insert(iterator pos, const T& val)`   | 在 pos 前插入 val，返回插入位置 |
| `iterator erase(iterator pos)`                  | 删除 pos 处元素，返回下一元素   |
| `iterator erase(iterator first, iterator last)` | 删除区间 [first, last) 内元素   |
| `T& operator[](size_t pos)`                     | 下标访问（不检查边界）          |
| `T& front()`                                    | 首元素                          |
| `T& back()`                                     | 尾元素                          |
| `void resize(size_t count)`                     | 调整大小为 count                |
| `void reserve(size_t new_cap)`                  | 预留容量                        |

#### 2. `deque`（双端队列）

| 方法签名                                      | 说明         |
| --------------------------------------------- | ------------ |
| `void push_front(const T& val)`               | 头部添加元素 |
| `void pop_front()`                            | 删除头部元素 |
| `void push_back(const T& val)`                | 尾部添加元素 |
| `void pop_back()`                             | 删除尾部元素 |
| `T& operator[](size_t pos)`                   | 下标访问     |
| `T& front()`                                  | 首元素       |
| `T& back()`                                   | 尾元素       |
| `iterator insert(iterator pos, const T& val)` | 同 vector    |
| `iterator erase(iterator pos)`                | 同 vector    |

#### 4. `string`（字符串）

| 方法签名                                             | 说明                      |
| ---------------------------------------------------- | ------------------------- |
| `size_t size() / length()`                           | 长度                      |
| `const char* c_str()`                                | 返回 C 风格字符串         |
| `void clear()`                                       | 清空                      |
| `char& operator[](size_t pos)`                       | 下标访问                  |
| `string& append(const string& str)`                  | 追加                      |
| `string& insert(size_t pos, const string& str)`      | 插入                      |
| `string& erase(size_t pos = 0, size_t count = npos)` | 删除子串                  |
| `size_t find(const string& str, size_t pos = 0)`     | 查找子串，返回下标或 npos |
| `string substr(size_t pos = 0, size_t count = npos)` | 取子串                    |
| `int compare(const string& str)`                     | 比较，返回负数/0/正数     |

#### 5. `set`（有序集合）

| 方法签名                                            | 说明                                  |
| --------------------------------------------------- | ------------------------------------- |
| `pair<iterator,bool> insert(const T& val)`          | 插入（返回是否成功）                  |
| `iterator find(const T& val)`                       | 查找，返回迭代器，未找到返回 end()    |
| `size_t count(const T& val)`                        | 返回 val 的出现次数                   |
| `iterator lower_bound(const T& val)`                | 第一个 >= val 的元素                  |
| `iterator upper_bound(const T& val)`                | 第一个 > val 的元素                   |
| `pair<iterator,iterator> equal_range(const T& val)` | 返回等于 val 的区间                   |
| `size_t erase(const T& val)`                        | 删除所有等于 val 的元素，返回删除个数 |
| `iterator erase(iterator pos)`                      | 删除 pos 处元素                       |

#### 6. `map`（有序映射）

| 方法签名                                              | 说明                   |
| ----------------------------------------------------- | ---------------------- |
| `T& operator[](const Key& key)`                       | 访问或插入（若不存在） |
| `T& at(const Key& key)`                               | 带检查访问             |
| `pair<iterator,bool> insert(const pair<Key,T>& kv)`   | 插入键值对             |
| `iterator find(const Key& key)`                       | 查找键，返回迭代器     |
| `size_t count(const Key& key)`                        | 出现次数               |
| `iterator lower_bound(const Key& key)`                | 第一个键 >= key 的元素 |
| `iterator upper_bound(const Key& key)`                | 第一个键 > key 的元素  |
| `pair<iterator,iterator> equal_range(const Key& key)` | 返回键为 key 的区间    |
| `size_t erase(const Key& key)`                        | 删除键为 key 的元素    |

#### 7. `unordered_set` / `unordered_map`（哈希集合/映射）

| 方法签名                                   | 说明                             |
| ------------------------------------------ | -------------------------------- |
| `pair<iterator,bool> insert(const T& val)` | 插入（返回是否成功）             |
| `iterator find(const T& val)`              | 查找                             |
| `size_t count(const T& val)`               | 出现次数                         |
| `size_t erase(const T& val)`               | 删除                             |
| `T& operator[](const Key& key)`            | **仅 unordered_map**：访问或插入 |

#### 8. 容器适配器

#### `stack`（栈）

| 方法签名                  | 说明           |
| ------------------------- | -------------- |
| `void push(const T& val)` | 压栈           |
| `void pop()`              | 弹栈（无返回） |
| `T& top()`                | 返回栈顶       |
| `bool empty()`            | 判空           |
| `size_t size()`           | 大小           |

#### `queue`（队列）

| 方法签名                  | 说明           |
| ------------------------- | -------------- |
| `void push(const T& val)` | 入队           |
| `void pop()`              | 出队（无返回） |
| `T& front()`              | 返回队首       |
| `T& back()`               | 返回队尾       |
| `bool empty()`            | 判空           |
| `size_t size()`           | 大小           |

#### `priority_queue`（优先队列，默认最大堆）

| 方法签名                  | 说明     |
| ------------------------- | -------- |
| `void push(const T& val)` | 插入元素 |
| `void pop()`              | 删除堆顶 |
| `const T& top()`          | 返回堆顶 |
| `bool empty()`            | 判空     |
| `size_t size()`           | 大小     |

---

### STL函数

#### 1. 排序与查找

| 算法签名                                                                               | 说明                      |
| -------------------------------------------------------------------------------------- | ------------------------- |
| `void sort(RandomIt first, RandomIt last[, Compare comp])`                             | 排序(默认升序)            |
| `InputIt find(InputIt first, InputIt last, const T& val)`                              | 查找第一个等于 val 的元素 |
| `InputIt find_if(InputIt first, InputIt last, UnaryPred p)`                            | 查找第一个满足 p 的元素   |
| `bool binary_search(ForwardIt first, ForwardIt last, const T& val)`                    | 二分查找是否存在          |
| `ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& val)`                 | 第一个 >= val             |
| `ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& val)`                 | 第一个 > val              |
| `pair<ForwardIt,ForwardIt> equal_range(ForwardIt first, ForwardIt last, const T& val)` | 等于 val 的区间           |

#### 2. 修改与操作

| 算法签名                                                          | 说明                              |
| ----------------------------------------------------------------- | --------------------------------- |
| `void fill(ForwardIt first, ForwardIt last, const T& val)`        | 填充                              |
| `ForwardIt remove(ForwardIt first, ForwardIt last, const T& val)` | 移除等于 val 的元素（返回新结尾） |
| `ForwardIt unique(ForwardIt first, ForwardIt last)`               | 移除连续重复元素                  |
| `void reverse(BidirIt first, BidirIt last)`                       | 反转                              |

#### 3. 数值算法

| 算法签名                                            | 说明                 |
| --------------------------------------------------- | -------------------- |
| `T accumulate(InputIt first, InputIt last, T init)` | 累加（可自定义操作） |
| `void iota(ForwardIt first, ForwardIt last, T val)` | 填充递增序列         |
| `const T& min(const T& a, const T& b)`              | 较小值               |
| `const T& max(const T& a, const T& b)`              | 较大值               |

---


