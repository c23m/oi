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

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;

class Solution;

enum Team
{
    none = 0,
    red,
    blue
};

enum Type
{
    dragon = 0,
    ninja,
    iceman,
    lion,
    wolf
};

class Headquarter
{
public:
    Team team;
    int elements;
    int count = 0;
    vector<Type> order;
    int position;
    deque<Unit *> units;
    deque<Unit *> *enemys;
    void init(Team team)
    {
        this->team = team;
        elements = solver.m;
        if (team == red)
        {
            order = {iceman, lion, wolf, ninja, dragon};
            position = 0;
            enemys = &solver.blueHome.units;
        }
        else
        {
            order = {lion, dragon, ninja, iceman, wolf};
            position = solver.n + 1;
            enemys = &solver.redHome.units;
        }
    }

    void spawn()
    {
        Type current = order[count % 5];
        if (elements >= solver.healths[current])
        {
        }
    }
};

class City
{
public:
    Team flag;
    int elements;
    Team lastWin;
    City()
    {
        flag = none;
        lastWin = none;
        elements = 0;
    }
};

class Unit
{
public:
    int elements;
    int force;
    int position;
    int id;
    bool win = false;
    Team team;

    Unit(Team team, Type type)
        : team(team), elements(solver.healths[type]), force(solver.attacks[type])
    {
    }

    virtual void attack(Unit &enemy)
    {
        enemy.elements -= force;
        if (enemy.elements <= 0)
        {
            win = true;
            enemy.dead();
        }
    }

    virtual void fightBack(Unit &enemy)
    {
        enemy.elements -= force / 2;
        if (enemy.elements <= 0)
        {
            win = true;
        }
    }

    virtual void dead()
    {
    }

    virtual void reward(int bonus)
    {
        elements += bonus;
    }

    virtual Type getType() = 0;
};

class Dragon : public Unit
{
public:
    Dragon(Team team) : Unit(team, Type::dragon)
    {
    }
    void reward(int bonus) override
    {
    }
};

class Ninja : public Unit
{
};

class Iceman : public Unit
{
};

class Lion : public Unit
{
};

class Wolf : public Unit
{
};

class Solution
{
public:
    int m, n, t;
    vector<int> healths;
    vector<int> attacks;

    Headquarter redHome;
    Headquarter blueHome;

    deque<Unit *> blueUnits;

    vector<City> citys;
    int hour = 0;
    int minute = 0;

    void init()
    {
        healths.resize(5);
        attacks.resize(5);
        cin >> m >> n >> t;
        for (int i = 0; i < 5; i++)
        {
            cin >> healths[i];
        }
        for (int i = 0; i < 5; i++)
        {
            cin >> attacks[i];
        }
        citys.resize(n + 1);
        redHome.init(red);
        blueHome.init(blue);
    }

    bool nextTime()
    {
        if (t - hour * 60 - minute >= 10)
        {
            minute += 10;
            if (minute == 60)
            {
                minute = 0;
                hour++;
                return true;
            }
        }
        else
            return false;
    }

    void solve()
    {
        init();

        switch (minute)
        {
        case 0:
            redHome.spawn();
            blueHome.spawn();
            break;
        case 10:
            break;
        case 20:
            break;
        case 30:
            break;
        case 40:
            break;
        case 50:
            break;
        }
        if (!nextTime())
        {
            return;
        }
    }

    void outputTime()
    {
        cout << setw(3) << setfill('0') << hour << ':' << setw(2) << minute << ' ';
    }
} solver;

signed main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "Case:" << i << '\n';
        solver.solve();
    }
    return 0;
}
```