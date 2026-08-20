# C++ 基础对象语法

在竞赛中，我们经常需要定义一种**包含数据和操作的数据类型**。

例如并查集：

```cpp
DSU dsu;
dsu.find(x);
dsu.unite(x, y);
```

线段树：

```cpp
SegmentTree tree;
tree.update(...);
tree.query(...);
```

这些代码看起来和普通函数不一样。

本章只学习理解这些代码所需要的基础语法。

**不涉及继承、多态等高级面向对象内容。**

---

# 一、先回顾最基础的 `struct`

假设我们需要表示一个二维点。

不用 `struct`，可能需要两个变量：

```cpp
int x;
int y;
```

如果有很多个点，就会变得混乱。

可以把它们放进一个结构体：

```cpp
struct Point
{
    int x;
    int y;
};
```

这样 `Point` 就成为了一种新的数据类型。

可以像使用 `int` 一样使用它：

```cpp
Point a;
Point b;
```

其中：

```cpp
a
```

和：

```cpp
b
```

叫做 **对象**。

---

## 访问对象的数据

使用 `.`：

```cpp
a.x = 3;
a.y = 4;

cout << a.x << ' ' << a.y;
```

可以理解为：

```text
a.x
│ │
│ └─ 成员变量
└─── 对象
```

所以：

```cpp
a.x
```

就是：

> `a` 这个对象中的 `x`。

---

# 二、`struct` 不只能存数据

前面的 `Point`：

```cpp
struct Point
{
    int x;
    int y;
};
```

里面只有数据。

实际上，`struct` 里面还可以写函数。

例如：

```cpp
struct Point
{
    int x;
    int y;

    void print()
    {
        cout << x << ' ' << y << '\n';
    }
};
```

这里的 `print` 就是一个**成员函数**。

---

## 怎么调用成员函数？

先创建对象：

```cpp
Point a;
a.x = 3;
a.y = 4;
```

然后：

```cpp
a.print();
```

这里的：

```cpp
a.print()
```

表示：

> 调用 `a` 这个对象的 `print` 函数。

---

## 成员函数为什么可以直接使用 `x`？

注意：

```cpp
struct Point
{
    int x;
    int y;

    void print()
    {
        cout << x << ' ' << y << '\n';
    }
};
```

`print()` 里面没有写：

```cpp
a.x
a.y
```

而是直接写：

```cpp
x
y
```

因为这个函数属于 `Point` 对象。

当我们调用：

```cpp
a.print();
```

实际上可以理解成：

> 让 `a` 这个对象执行 `print()`。

因此 `print()` 里面访问的 `x` 和 `y`，就是 `a.x` 和 `a.y`。

---

# 三、为什么要把函数放进 `struct`？

这是初学者很容易产生的问题。

例如并查集。

传统写法可能是：

```cpp
vector<int> parent;

int find(int x)
{
    ...
}

void unite(int x, int y)
{
    ...
}
```

如果程序里有很多数据结构：

```text
parent
tree
dist
...
```

函数和它操作的数据分散在一起。

于是可以把它们放进同一个 `struct`：

```cpp
struct DSU
{
    vector<int> parent;

    int find(int x)
    {
        ...
    }

    void unite(int x, int y)
    {
        ...
    }
};
```

现在：

```text
DSU
├── parent
├── find()
└── unite()
```

它们都属于 `DSU`。

使用时：

```cpp
DSU dsu;

dsu.find(x);
dsu.unite(x, y);
```

代码的含义就非常直观：

> 对 `dsu` 这个并查集执行 `find` 和 `unite`。

---

# 四、对象可以有多个

假设：

```cpp
DSU dsu1;
DSU dsu2;
```

那么：

```cpp
dsu1.find(x);
```

操作的是 `dsu1` 的数据。

而：

```cpp
dsu2.find(x);
```

操作的是 `dsu2` 的数据。

每个对象都有自己的一份成员变量。

例如：

```cpp
struct Counter
{
    int value = 0;

    void add()
    {
        value++;
    }
};
```

创建两个对象：

```cpp
Counter a;
Counter b;

a.add();
a.add();
b.add();
```

此时：

```cpp
a.value == 2
b.value == 1
```

因为 `a` 和 `b` 是两个不同的对象。

---

# 五、构造函数

前面的 `DSU` 有一个问题。

假设：

```cpp
struct DSU
{
    vector<int> parent;

    int find(int x)
    {
        ...
    }
};
```

创建：

```cpp
DSU dsu;
```

这时候 `parent` 还没有按照并查集的要求初始化。

我们当然可以：

```cpp
DSU dsu;
dsu.parent.resize(n + 1);

for (int i = 1; i <= n; i++)
    dsu.parent[i] = i;
```

但是每次创建 `DSU` 都这样写很麻烦。

因此可以让对象**创建的时候自动初始化**。

这就是构造函数。

---

## 最简单的构造函数

```cpp
struct Point
{
    int x;
    int y;

    Point(int a, int b)
    {
        x = a;
        y = b;
    }
};
```

这里：

```cpp
Point(int a, int b)
```

就是构造函数。

创建对象：

```cpp
Point p(3, 4);
```

创建 `p` 的时候，构造函数会自动执行：

```cpp
x = 3;
y = 4;
```

所以：

```cpp
p.x == 3
p.y == 4
```

---

# 六、构造函数为什么叫构造函数？

因为它在**构造对象的时候自动调用**。

例如：

```cpp
Point p(3, 4);
```

大致可以理解成：

```text
创建 Point 对象 p
        ↓
调用 Point(3, 4)
        ↓
x = 3
y = 4
        ↓
得到初始化完成的 p
```

我们不需要手动调用：

```cpp
p.Point(3, 4);  // 错误
```

构造函数会自动执行。

---

# 七、构造函数的常见写法

刚才写的是：

```cpp
struct Point
{
    int x;
    int y;

    Point(int a, int b)
    {
        x = a;
        y = b;
    }
};
```

竞赛代码里经常看到：

```cpp
struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};
```

这里第一次看会比较奇怪。

先不要把它想得太复杂。

```cpp
Point(int x, int y) : x(x), y(y) {}
```

和：

```cpp
Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
```

作用基本相同。

初学者现阶段只需要知道：

> `: x(x), y(y)` 是一种初始化成员变量的写法。

以后看到它能读懂即可。

---

# 八、默认参数可以让构造函数更方便

例如：

```cpp
struct Point
{
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}
};
```

现在三种写法都可以：

```cpp
Point a;
Point b(3);
Point c(3, 4);
```

分别得到：

```text
a = (0, 0)
b = (3, 0)
c = (3, 4)
```

原因就是：

```cpp
int x = 0
int y = 0
```

给参数提供了默认值。

---

# 九、回到并查集

现在我们已经有足够的知识，可以看一个真正的竞赛例子。

先不考虑路径压缩和按大小合并，只看对象语法。

```cpp
struct DSU
{
    vector<int> parent;

    DSU(int n)
    {
        parent.resize(n + 1);

        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x != y)
            parent[x] = y;
    }
};
```

使用：

```cpp
DSU dsu(5);

dsu.unite(1, 2);
dsu.unite(2, 3);

cout << dsu.find(1) << '\n';
```

现在逐部分看。

---

## `DSU dsu(5);`

创建一个 `DSU` 对象：

```cpp
DSU dsu(5);
```

因为传入了 `5`，所以自动调用：

```cpp
DSU(int n)
```

于是：

```cpp
parent
```

被初始化。

---

## `dsu.find(1)`

调用 `dsu` 的成员函数：

```cpp
dsu.find(1);
```

这个函数会使用：

```cpp
dsu.parent
```

因为 `find` 是 `DSU` 的成员函数。

---

## `dsu.unite(1, 2)`

调用：

```cpp
dsu
```

的：

```cpp
unite
```

函数。

因此：

```cpp
dsu.unite(1, 2);
```

可以理解成：

> 让 `dsu` 这个并查集把 1 和 2 合并。

---

# 十、对象作为函数参数

除了成员函数，普通函数也可以接收对象。

例如：

```cpp
struct Point
{
    int x;
    int y;
};

void print(Point p)
{
    cout << p.x << ' ' << p.y << '\n';
}
```

调用：

```cpp
Point a{3, 4};
print(a);
```

这里：

```cpp
Point p
```

表示：

> 函数接收一个 `Point` 对象。

---

## 为什么经常看到 `const Point&`？

竞赛代码中更常见：

```cpp
void print(const Point& p)
{
    cout << p.x << ' ' << p.y << '\n';
}
```

这里先只需要理解三个部分：

```text
const
 ↓
不能通过 p 修改对象

&
 ↓
不复制对象

Point
 ↓
p 是 Point 类型
```

因此：

```cpp
const Point& p
```

可以简单理解为：

> **以引用的方式使用这个对象，并且不修改它。**

对于初学者，先记住这种写法的用途即可，不需要深入研究引用实现原理。

---

# 十一、如果函数需要修改对象

例如：

```cpp
void move(Point& p)
{
    p.x++;
}
```

调用：

```cpp
Point a{1, 2};

move(a);
```

之后：

```cpp
a.x == 2
```

这里的：

```cpp
Point& p
```

表示：

> `p` 是传入对象本身的引用，因此可以修改原来的对象。

对比：

```cpp
const Point& p
```

和：

```cpp
Point& p
```

可以先记：

```text
const Point&   查看对象，不修改
Point&         可以修改对象
```

---

# 十二、对象可以作为返回值

函数也可以返回一个对象。

例如：

```cpp
Point add(Point a, Point b)
{
    return {a.x + b.x, a.y + b.y};
}
```

使用：

```cpp
Point a{1, 2};
Point b{3, 4};

Point c = add(a, b);
```

得到：

```text
c = (4, 6)
```

这和函数返回 `int` 没有本质区别：

```cpp
int add(int a, int b)
{
    return a + b;
}
```

只不过现在返回类型从：

```cpp
int
```

变成了：

```cpp
Point
```

---

# 十三、对象可以放进 `vector`

这在竞赛中非常常见。

```cpp
struct Point
{
    int x;
    int y;
};

vector<Point> points;
```

加入对象：

```cpp
points.push_back({1, 2});
points.push_back({3, 4});
```

访问：

```cpp
cout << points[0].x << '\n';
```

也可以：

```cpp
for (Point p : points)
    cout << p.x << ' ' << p.y << '\n';
```

因此你以后看到：

```cpp
vector<Edge> edges;
vector<Node> nodes;
vector<Point> points;
```

不要觉得特殊。

它们和：

```cpp
vector<int> a;
```

完全是同一种思想：

> `vector` 里面存的是某种类型的对象。

---

# 十四、运算符重载

最后介绍一个 ICPC 中比较常见，但稍微特殊的东西。

假设：

```cpp
struct Point
{
    int x;
    int y;
};
```

现在：

```cpp
vector<Point> points;
sort(points.begin(), points.end());
```

会出问题。

因为 `sort` 不知道：

> 两个 `Point` 谁“小”。

我们可以告诉它：

```cpp
struct Point
{
    int x;
    int y;

    bool operator<(const Point& other) const
    {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
```

这样：

```cpp
sort(points.begin(), points.end());
```

就知道如何比较两个 `Point`。

---

## 这个函数到底是什么？

```cpp
bool operator<(const Point& other) const
```

可以先理解成：

> 定义 `Point` 的 `<` 运算规则。

于是：

```cpp
a < b
```

就会调用这个函数。

例如：

```cpp
Point a{1, 2};
Point b{2, 3};

if (a < b)
    cout << "a is smaller";
```

实际上就是在执行我们定义的比较规则。

---

# 十五、为什么这里需要 `const`？

你可能会看到：

```cpp
bool operator<(const Point& other) const
```

两个 `const` 容易混淆。

现在只需要这样理解：

### 参数上的 `const`

```cpp
const Point& other
```

表示：

> 比较过程中不会修改 `other`。

### 最后的 `const`

```cpp
operator<(...) const
```

表示：

> 比较过程中不会修改当前对象。

所以整个函数就是一个“只读比较”。

初学阶段不需要进一步研究。

---

# 十六、嵌套 `struct`

最后看一个你以后一定会遇到的写法。

例如线段树：

```cpp
struct SegmentTree
{
    struct Node
    {
        int sum;
        int lazy;
    };

    vector<Node> tree;

    void update(int p, int l, int r)
    {
        ...
    }

    int query(int p, int l, int r)
    {
        ...
    }
};
```

这里有两个 `struct`。

外层：

```cpp
SegmentTree
```

表示整个线段树。

里面：

```cpp
Node
```

表示线段树的一个节点。

所以：

```cpp
vector<Node> tree;
```

就是：

> 用一个 `vector` 保存很多个节点。

这只是把前面学过的知识组合起来，并没有新的复杂概念。

---

# 十七、你需要掌握到什么程度？

对于 ICPC 初学者，这一章掌握下面这些就够了：

### 必须会

```text
struct
├── 成员变量
├── 成员函数
├── 创建对象
├── 使用 .
├── 构造函数
├── 对象作为参数
├── 对象作为返回值
├── vector<对象>
└── 嵌套 struct
```

### 需要看得懂

```text
const T&
初始化列表 : x(x)
operator<
```

### 暂时不用学

```text
继承
多态
虚函数
private / protected 的复杂设计
this 的深入用法
new / delete
智能指针
拷贝构造
移动构造
移动语义
复杂运算符重载
设计模式
```

---

## 最终理解目标

学完后，看到这样的代码：

```cpp
struct DSU
{
    vector<int> parent;

    DSU(int n) : parent(n + 1)
    {
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x != y)
            parent[x] = y;
    }
};
```

至少应该能够**逐行解释每一个语法**：

```text
struct DSU
    ↓
定义一种叫 DSU 的新类型

vector<int> parent
    ↓
DSU 对象里面有一个 parent

DSU(int n)
    ↓
创建 DSU 对象时自动执行的构造函数

int find(int x)
    ↓
DSU 的成员函数

void unite(int x, int y)
    ↓
DSU 的另一个成员函数
```

然后：

```cpp
DSU dsu(n);
dsu.unite(1, 2);
dsu.find(1);
```

能够理解成：

> **创建一个 `DSU` 对象 `dsu`，这个对象自己保存并查集的数据，并提供 `find`、`unite` 两个操作。**

达到这个程度，就已经足够支撑后面阅读**并查集、线段树、树状数组封装、几何 `Point`、图论 `Edge` 等绝大多数竞赛代码**了。

这才比较适合作为“**只会基础 `struct` 的新人 → 能看懂竞赛对象式代码**”的一章。
