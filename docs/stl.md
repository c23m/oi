# C++ STL
---

## 一、容器概览

| 类别         | 容器                              | 特点                           |
| ------------ | --------------------------------- | ------------------------------ |
| 顺序容器     | `vector`                          | 动态数组，随机访问，尾部操作快 |
|              | `deque`                           | 双端队列，两端操作快，随机访问 |
|              | `string`                          | 字符串，可视为 `vector<char>`  |
| 关联容器     | `set`                             | 有序集合，红黑树，键唯一       |
|              | `map`                             | 有序映射，键值对，键唯一       |
| 无序关联容器 | `unordered_set` / `unordered_map` | 哈希集合/映射，平均 O(1) 操作  |
| 容器适配器   | `stack`                           | 栈，LIFO                       |
|              | `queue`                           | 队列，FIFO                     |
|              | `priority_queue`                  | 优先队列，默认最大堆           |

---

## 二、通用容器方法

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

---

## 三、常用容器详解

### 1. `vector`

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

### 2. `deque`（双端队列）

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

### 4. `string`（字符串）

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

### 5. `set`（有序集合）

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

### 6. `map`（有序映射）

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

### 7. `unordered_set` / `unordered_map`（哈希集合/映射）

| 方法签名                                   | 说明                             |
| ------------------------------------------ | -------------------------------- |
| `pair<iterator,bool> insert(const T& val)` | 插入（返回是否成功）             |
| `iterator find(const T& val)`              | 查找                             |
| `size_t count(const T& val)`               | 出现次数                         |
| `size_t erase(const T& val)`               | 删除                             |
| `T& operator[](const Key& key)`            | **仅 unordered_map**：访问或插入 |

### 8. 容器适配器

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

## 四、通用算法

### 1. 排序

| 算法签名                                                                               | 说明                      |
| -------------------------------------------------------------------------------------- | ------------------------- |
| `void sort(RandomIt first, RandomIt last[, Compare comp])`                             | 排序(默认升序)            |
| `InputIt find(InputIt first, InputIt last, const T& val)`                              | 查找第一个等于 val 的元素 |
| `InputIt find_if(InputIt first, InputIt last, UnaryPred p)`                            | 查找第一个满足 p 的元素   |
| `bool binary_search(ForwardIt first, ForwardIt last, const T& val)`                    | 二分查找是否存在          |
| `ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& val)`                 | 第一个 >= val             |
| `ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& val)`                 | 第一个 > val              |
| `pair<ForwardIt,ForwardIt> equal_range(ForwardIt first, ForwardIt last, const T& val)` | 等于 val 的区间           |

### 3. 修改与操作

| 算法签名                                                          | 说明                              |
| ----------------------------------------------------------------- | --------------------------------- |
| `void fill(ForwardIt first, ForwardIt last, const T& val)`        | 填充                              |
| `ForwardIt remove(ForwardIt first, ForwardIt last, const T& val)` | 移除等于 val 的元素（返回新结尾） |
| `ForwardIt unique(ForwardIt first, ForwardIt last)`               | 移除连续重复元素                  |
| `void reverse(BidirIt first, BidirIt last)`                       | 反转                              |

### 4. 数值算法

| 算法签名                                            | 说明                 |
| --------------------------------------------------- | -------------------- |
| `T accumulate(InputIt first, InputIt last, T init)` | 累加（可自定义操作） |
| `void iota(ForwardIt first, ForwardIt last, T val)` | 填充递增序列         |
| `const T& min(const T& a, const T& b)`              | 较小值               |
| `const T& max(const T& a, const T& b)`              | 较大值               |

---

## 五、基础语法示例

### 1. 创建容器

```cpp
// 栈上创建
vector<int> v1;                         // 空vector
vector<int> v2(10, 5);                  // 10个5
vector<int> v3{1, 2, 3, 4};             // 列表初始化

map<string, int> mp;                    // 空map
mp["one"] = 1;                          // 插入

// 堆上创建（使用智能指针，推荐）
auto pv = make_unique<vector<int>>(5, 10); // C++14
```

### 2. 基本操作

```cpp
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
```

### 3. 算法使用

```cpp
vector<int> a = {5, 2, 8, 1, 9};
// 排序
sort(a.begin(), a.end());               // 升序
// 二分查找（需有序）
bool found = binary_search(a.begin(), a.end(), 8);
// 去重
a.erase(unique(a.begin(), a.end()), a.end());
// 反转
reverse(a.begin(), a.end());
// 累加
int sum = accumulate(a.begin(), a.end(), 0);
// 查找
auto it = find(a.begin(), a.end(), 8);
if (it != a.end()) cout << *it;
```

---

## 六、模板示例

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
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```