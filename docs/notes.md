- [算法竞赛常用模板速查](#算法竞赛常用模板速查)
  - [模板](#模板)
  - [思想](#思想)
    - [二分答案](#二分答案)
    - [前缀和](#前缀和)
    - [二维前缀和](#二维前缀和)
    - [差分](#差分)
    - [离散化](#离散化)
    - [位运算常用](#位运算常用)
  - [数据结构](#数据结构)
    - [并查集](#并查集)
    - [ST表](#st表)
    - [单调栈](#单调栈)
    - [单调队列](#单调队列)
    - [树状数组](#树状数组)
    - [线段树](#线段树)
  - [图论](#图论)
    - [DFS](#dfs)
    - [BFS](#bfs)
    - [拓扑排序（Kahn）](#拓扑排序kahn)
    - [Dijkstra](#dijkstra)
    - [Kruskal](#kruskal)
    - [LCA 倍增](#lca-倍增)
  - [动态规划](#动态规划)
    - [背包](#背包)
    - [0‑1 背包](#01-背包)
    - [完全背包](#完全背包)
    - [多重背包](#多重背包)
    - [分组背包](#分组背包)
    - [LIS（最长严格上升子序列）](#lis最长严格上升子序列)
    - [最大子段和](#最大子段和)
  - [数论基础](#数论基础)
    - [快速幂](#快速幂)
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
正式使用版本。
```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

#define int long long

#define all(x) (x).begin(), (x).end()
#define pb push_back

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << x << endl;
#else
#define debug(x)
#endif

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;

void solve()
{
}

signed main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
```

## 思想

### 二分答案
用于答案满足单调性的情况。
```cpp
// 判断是否可行
bool check(int x);

int maximumFeasible(int left, int right)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (check(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }

    return right;
}

int minimumFeasible(int left, int right)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (check(mid))
            right = mid - 1;
        else
            left = mid + 1;
    }

    return left;
}
```

### 前缀和

用于静态下的区间和查询。  
> 本部分以下标1为起点。

```cpp
vector<int> prefixSum(vector<int>& nums)
{
    int n = nums.size() - 1;
    vector<int> pref(n + 1);

    for (int i = 1; i <= n; i++)
    {
        pref[i] = pref[i - 1] + nums[i];
    }

    return pref;
}

int getSum(vector<int>& pref, int l, int r){
    return pref[r] - pref[l - 1];
}
```

### 二维前缀和

用于静态矩阵中的子矩阵和查询。

```cpp
vector<vector<int>> prefixSum2D(vector<vector<int>>& nums)
{
    int n = nums.size() - 1;
    int m = nums[0].size() - 1;

    vector<vector<int>> pref(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + nums[i][j];
        }
    }

    return pref;
}

vector<int> getSum(vector<vector<int>> pref, int x1, int y1, int x2, int y2){
    return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
}
```

### 差分

用于静态下的区间加和单点查询。

```cpp
vector<int> difference(vector<int>& nums)
{
    int n = nums.size() - 1;
    vector<int> diff(n + 1);

    for (int i = 1; i <= n; i++)
    {
        diff[i] = nums[i] - nums[i - 1];
    }

    return diff;
}

// 区间 [l, r] 的所有元素加 x
void add(vector<int>& diff, int l, int r, int x)
{
    int n = diff.size() - 1;
    diff[l] += x;
    if (r < n)
    {
        diff[r + 1] -= x;
    }
}

//恢复原数组
vector<int> restore(vector<int>& diff)
{
    int n = diff.size() - 1;
    vector<int> nums(n + 1);

    for (int i = 1; i <= n; i++)
    {
        nums[i] = nums[i - 1] + diff[i];
    }

    return nums;
}
```

### 离散化

用于将数值较大或范围较分散的数据映射到连续的整数编号。

```cpp
unordered_map<int, int> discretize(vector<int> &nums)
{
    vector<int> tmp(nums);
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

    unordered_map<int, int> disc;
    for (int i = 0; i < tmp.size(); i++)
    {
        disc[tmp[i]] = i;
    }

    return disc;
}
```

### 位运算常用

- 取出 `x` 的第 `k` 位：`(x >> k) & 1`
- 将 `x` 的第 `k` 位设置为 `1`：`x | (1 << k)`
- 将 `x` 的第 `k` 位设置为 `0`：`x & ~(1 << k)`
- 取最低位的 `1`：`x & -x`
- 判断 `x`(x>0) 是否为 `2` 的幂：`(x & (x - 1)) == 0`


## 数据结构

### 并查集
这是最简单的版本。
```cpp
struct DSU {
    vector<int> fa;

    DSU(int n) {
        fa.resize(n);
        for (int i = 0; i < n; i++){
            fa[i] = i;
        }
    }
    int find(int u) {
        if(fa[u] == u)
            return u;
        return fa[u] = find(fa[u]);
    }
    void unite(int u, int v) {
        int ru = find(u);
        int rv = find(v);

        fa[rv] = ru;
    }
};
```

### ST表
本代码用于求区间最大值。
```cpp
struct STTable{
    int n, LOG;
    vector<vector<int>> f;
    STTable(vector<int>& nums){
        n = nums.size();
        LOG = log2(n) + 1;
        f.assign(n, vector<int>(LOG));
        for (int i = 0; i < n; i++)
        {
            f[i][0] = nums[i];
        }
        for (int j = 1; j < LOG; j++)
        {
            for (int i = 0; i + (1 << j) - 1 < n; i++)
            {
                f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    int query(int l, int r){
        int s = log2(r - l + 1);
        return max(f[l][s], f[r - (1 << s) + 1][s]);
    }
};
```

### 单调栈
下一个更大元素
```cpp
vector<int> nextLarger(vector<int>& nums){
    int n = nums.size();
    vector<int> nxt(n, -1);
    stack<int> st;
    for (int i = 0; i<n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            nxt[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nxt;
}
```

### 单调队列
固定长度区间的最大值
```cpp
vector<int> intervalMaximum(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> ans(n - k + 1);
    deque<int> dq;
    for (int r = 0; r < n; r++)
    {
        while (!dq.empty() && nums[dq.back()] < nums[r])
        {
            dq.pop_back();
        }
        dq.push_back(r);
        int l = r - k + 1;
        if (l < 0)
            continue;
        if (dq.front() < l)
            dq.pop_front();
        ans[l] = nums[dq.front()];
    }
    return ans;
}
```

### 树状数组
用于单点修改, 区间查询
或区间修改，单点查询（差分）
```cpp
struct FenwickTree // 1-base
{
    vector<int> bit;
    int n;
    FenwickTree(vector<int> &nums, bool diff = false){ //diff=true: 改为差分模式
        n = nums.size() - 1;
        bit.resize(n + 1);

        for (int i = 1; i <= n; i++)
        {
            bit[i] += nums[i];
            if(diff)
                bit[i] -=  nums[i-1];
            int nxt = i + (i & -i);
            if (nxt <= n)
            {
                bit[nxt] += bit[i];
            }
        }
    }
    void add(int i, int x)
    {
        while (i <= n)
        {
            bit[i] += x;
            i += i & -i;
        }
    }

    void add(int l, int r, int x) // diff
    {
        add(l, x);
        add(r + 1, -x);
    }

    int sum(int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }

    int query(int l, int r){
        return sum(r) - sum(l-1);
    }

    int query(int i){ // diff
        return sum(i);
    }
};
```

### 线段树

```cpp
struct SegmentTree
{
    struct Node
    {
        int sum;
        int l, r;
        int lazyAdd;
    };
    // 1-based
    int n;
    vector<Node> tree;

    SegmentTree(vector<int> &nums)
    {
        n = nums.size() - 1;
        tree.resize(n * 4);
        build(1, 1, n, nums);
    }

    void pull(int node)
    {
        tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    }

    void apply(int node, int value)
    {
        tree[node].sum += (tree[node].r - tree[node].l + 1) * value;
        tree[node].lazyAdd += value;
    }

    void push(int node)
    {
        if (tree[node].lazyAdd == 0 || tree[node].l == tree[node].r)
            return;
        apply(node * 2, tree[node].lazyAdd);
        apply(node * 2 + 1, tree[node].lazyAdd);
        tree[node].lazyAdd = 0;
    }

    void build(int node, int left, int right, vector<int> &nums)
    {
        if (left == right)
        {
            tree[node].sum = nums[left];
            tree[node].l = left;
            tree[node].r = right;
            return;
        }
        int mid = (left + right) / 2;
        tree[node].l = left;
        tree[node].r = right;
        build(node * 2, left, mid, nums);
        build(node * 2 + 1, mid + 1, right, nums);
        pull(node);
    }

    void update(int left, int right, int value, int node = 1)
    {
        if (left <= tree[node].l && tree[node].r <= right)
        {
            apply(node, value);
            return;
        }
        push(node);
        int mid = (tree[node].l + tree[node].r) / 2;
        if (left <= mid)
            update(left, right, value, node * 2);
        if (right > mid)
            update(left, right, value, node * 2 + 1);
        pull(node);
    }

    int query(int left, int right, int node = 1)
    {
        if (left <= tree[node].l && tree[node].r <= right)
            return tree[node].sum;
        push(node);
        int mid = (tree[node].l + tree[node].r) / 2;
        int answer = 0;
        if (left <= mid)
            answer += query(left, right, node * 2);
        if (right > mid)
            answer += query(left, right, node * 2 + 1);
        return answer;
    }
};
```

## 图论

### DFS
用于遍历图或求连通块。
```cpp
void dfs(vector<vector<int>> &g, int u, vector<char> &vis)
{
    vis[u] = true;
    for (int v : g[u])
    {
        if (!vis[v])
            dfs(g, v, vis);
    }
}
```

### BFS
用于求无权图中从起点出发的最短路径。
```cpp
vector<int> bfs(vector<vector<int>> &g, int s)
{
    queue<int> q;
    vector<int> dist(g.size(), -1);

    dist[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : g[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}
```

### 拓扑排序（Kahn）
用于有向图的拓扑排序，并可检测是否存在环。

```cpp
vector<int> topoSort(vector<vector<int>> &g)
{
    int n = g.size() - 1;
    vector<int> indeg(n + 1);
    for (int u = 1; u <= n; u++)
    {
        for (int v : g[u])
        {
            indeg[v]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
            q.push(i);
    }

    vector<int> topo;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v : g[u])
        {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }

    return topo;
}
```
`topo.size() != n` 则存在环. 

### Dijkstra

单源最短路径
```cpp

vector<int> dijkstra(vector<vector<pair<int, int>>> &g, int s)
{
    int n = g.size() - 1;
    vector<int> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

### Kruskal
用于求无向图的最小生成树。  
参看[并查集](#并查集)。

```cpp
struct Edge
{
    int u, v, w;
};

pair<int, bool> kruskal(int n, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
    {
        return a.w < b.w;
    });

    DSU dsu(n);

    int ans = 0;
    int cnt = 0;

    for (auto [u, v, w] : edges)
    {
        if (dsu.find(u) != dsu.find(v))
        {
            dsu.unite(u, v);
            ans += w;
            cnt++;

            if (cnt == n - 1)
                break;
        }
    }

    return {ans, cnt == n - 1};
}
```

---

### LCA 倍增

用于查询树上两个节点的最近公共祖先。  
预处理复杂度：`O(n log n)`。  
单次查询复杂度：`O(log n)`。

```cpp
struct LCA // 1-based
{
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> f;

    LCA(vector<vector<int>> &g, int root = 1)
    {
        n = g.size() - 1;
        LOG = log2(n) + 1;

        depth.resize(n + 1);
        f.assign(n + 1, vector<int>(LOG));

        depth[root] = 1;
        dfs(root, g);

        for (int j = 1; j < LOG; j++)
        {
            for (int i = 1; i <= n; i++)
            {
                f[i][j] = f[f[i][j - 1]][j - 1];
            }
        }
    }

    void dfs(int u, vector<vector<int>> &g)
    {
        for (int v : g[u])
        {
            if (depth[v] != 0)
                continue;

            depth[v] = depth[u] + 1;
            f[v][0] = u;

            dfs(v, g);
        }
    }

    int query(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);

        for (int j = LOG - 1; j >= 0; j--)
        {
            if (depth[f[u][j]] >= depth[v])
                u = f[u][j];
        }

        if (u == v)
            return u;

        for (int j = LOG - 1; j >= 0; j--)
        {
            if (f[u][j] != f[v][j])
            {
                u = f[u][j];
                v = f[v][j];
            }
        }

        return f[u][0];
    }
};
```

## 动态规划

### 背包

### 0‑1 背包
```cpp

int zeroOneKnapsack(vector<pair<int, int>> &items, int capacity)
{
    vector<int> dp(capacity + 1);

    for (auto [w, v] : items)
    {
        for (int j = capacity; j >= w; j--)
        {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    return dp[capacity];
}
```

### 完全背包
每种物品可以选择任意次。
```cpp
int completeKnapsack(vector<pair<int, int>> &items, int capacity)
{
    vector<int> dp(capacity + 1);

    for (auto [w, v] : items)
    {
        for (int j = w; j <= capacity; j++)
        {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    return dp[capacity];
}
```

### 多重背包
每种物品最多选择 `count` 次。
```cpp
struct Item
{
    int weight;
    int value;
    int count;
};

int multipleKnapsack(vector<Item> &items, int capacity)
{
    vector<pair<int, int>> splitItems;

    for (auto [weight, value, count] : items)
    {
        int k = 1;

        while (count >= k)
        {
            splitItems.push_back({weight * k, value * k});
            count -= k;
            k *= 2;
        }

        if (count > 0)
        {
            splitItems.push_back({weight * count, value * count});
        }
    }

    vector<int> dp(capacity + 1);

    for (auto [weight, value] : splitItems)
    {
        for (int j = capacity; j >= weight; j--)
        {
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }

    return dp[capacity];
}
```

### 分组背包
每组最多选择一个物品。
```cpp
int groupedKnapsack(vector<vector<pair<int, int>>> &groups, int capacity)
{
    vector<int> dp(capacity + 1);

    for (auto &group : groups)
    {
        for (int j = capacity; j >= 0; j--)
        {
            for (auto [weight, value] : group)
            {
                if (weight <= j)
                {
                    dp[j] = max(dp[j], dp[j - weight] + value);
                }
            }
        }
    }

    return dp[capacity];
}
```

### LIS（最长严格上升子序列）
使用贪心和二分查找。  
时间复杂度：`O(n log n)`。
```cpp
int LIS(vector<int> &nums)
{
    vector<int> tails;
    for (int x : nums)
    {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }
    return tails.size();
}
```

### 最大子段和
时间复杂度：`O(n)`。
```cpp
int kadane(vector<int> &nums)
{
    int current = nums[0];
    int answer = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        current = max(nums[i], current + nums[i]);
        answer = max(answer, current);
    }

    return answer;
}
```

---

## 数论基础

### 快速幂
下面的算法求 $a^b \bmod p$ 的结果。

x 的逆元为 $x^{p-2} \bmod p$, 即 `qpow(x, p - 2, p)`
```cpp
long long qpow(long long a, long long b, long long p) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
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


