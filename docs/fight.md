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
    bool reached = false;
    void init(Team team)
    {
        this->team = team;
        elements = solver.m;
        if (team == red)
        {
            order = {iceman, lion, wolf, ninja, dragon};
            position = 0;
        }
        else
        {
            order = {lion, dragon, ninja, iceman, wolf};
            position = solver.n + 1;
        }
    }

    void spawn()
    {
        Type current = order[count % 5];
        if (elements < solver.healths[current])
        {
            if (team == red)
            {
                solver.redUnits.push_front(nullptr);
                solver.redUnits.pop_back();
            }
            else
            {
                solver.blueUnits.push_back(nullptr);
                solver.redUnits.pop_front();
            }
            return;
        }

        elements -= solver.healths[current];
        Unit *Obj;
        switch (current)
        {
        case dragon:
            Obj = new Dragon(team);
        case ninja:
            Obj = new Ninja(team);
        case iceman:
            Obj = new Iceman(team);
        case lion:
            Obj = new Lion(team);
        case wolf:
            Obj = new Wolf(team);
        }
        if (team == red)
        {
            solver.redUnits.push_front(Obj);
            solver.redUnits.pop_back();
        }
        else
        {
            solver.blueUnits.push_back(Obj);
            solver.redUnits.pop_front();
        }
        solver.outputTime();
        Obj->outputInfo();
        cout << "born" << '\n';
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

    void march()
    {
        if (team == red)
            position++;
        else
            position--;
        if (position == 0 || position == solver.n + 1)
        {
            solver.outputTime();
            outputInfo();
            cout << "reached ";
            cout << (team == red ? "blue " : "red ");
            cout << "headquarter ";
            outputWith();
            cout << '/n';
            Headquarter &enemyHome = team == red ? solver.redHome : solver.blueHome;
            if (!enemyHome.reached)
            {
                enemyHome.reached = true;
            }
            else
            {
                solver.outputTime();
                cout << (team == red ? "blue " : "red ");
                cout << "headquarter was taken";
                cout << '/n';
                solver.ending = true;
            }
        }
        else
        {
            solver.outputTime();
            outputInfo();
            cout << "was killed ";
            outputLocation();
            cout << '/n';
        }
    }

    virtual void attack(Unit &enemy)
    {

        enemy.elements -= force;
        if (enemy.elements <= 0)
        {
            win = true;
            enemy.dead();
            if (getType() == dragon)
            {
                static_cast<Dragon &>(*this).yell();
            }
        }
        else
        {
            enemy.fightBack(*this);
        }
    }

    virtual void fightBack(Unit &enemy)
    {
        enemy.elements -= force / 2;
        if (enemy.elements <= 0)
        {
            win = true;
        }
        else if (enemy.getType() == dragon)
        {
            static_cast<Dragon &>(enemy).yell();
        }
    }

    virtual void dead()
    {
        solver.outputTime();
        outputInfo();
        cout << "was killed ";
        outputLocation();
        cout << '/n';
    }

    virtual void reward(int bonus)
    {
        elements += bonus;
    }

    virtual Type getType() = 0;

    void outputInfo()
    {
        vector<string> types =
            {"dragon", "ninja", "iceman", "lion", "wolf"};
        string teamStr = team == red ? "red " : "blue ";
        cout << teamStr << types[getType()] << ' ' << id << ' ';
    }

    void outputWith()
    {
        cout << elements << ' ' << "elements and force " << force;
    }

    void outputLocation()
    {
        cout << "in city " << position << ' ';
    }
};

class Dragon : public Unit
{
public:
    Dragon(Team team) : Unit(team, Type::dragon)
    {
    }

    void yell()
    {
        solver.outputTime();
        outputInfo();
        cout << "yelled ";
        outputLocation();
        cout << '/n';
    }

    Type getType() override
    {
        return dragon;
    }
};

class Ninja : public Unit
{
public:
    Ninja(Team team) : Unit(team, Type::ninja)
    {
    }

    void fightBack(Unit &enemy) override
    {
        if (enemy.getType() == dragon)
        {
            static_cast<Dragon &>(enemy).yell();
        }
    }

    Type getType() override
    {
        return ninja;
    }
};

class Iceman : public Unit
{
public:
    Iceman(Team team) : Unit(team, Type::iceman)
    {
    }

    Type getType() override
    {
        return iceman;
    }
};

class Lion : public Unit
{
public:
    int originHp;
    Lion(Team team) : Unit(team, Type::lion), originHp(elements)
    {
    }

    Type getType() override
    {
        return lion;
    }
};

class Wolf : public Unit
{
public:
    Wolf(Team team) : Unit(team, Type::wolf)
    {
    }

    Type getType() override
    {
        return wolf;
    }
};

class Solution
{
public:
    int m, n, t;
    vector<int> healths;
    vector<int> attacks;

    Headquarter redHome;
    Headquarter blueHome;

    deque<Unit *> redUnits;
    deque<Unit *> blueUnits;

    vector<City> citys;
    int hour = 0;
    int minute = 0;

    bool ending = false;
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

    void nextTime()
    {
        if (t - hour * 60 - minute >= 10)
        {
            minute += 10;
            if (minute == 60)
            {
                minute = 0;
                hour++;
            }
        }
        else
            ending = true;
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
        nextTime();
        if (ending)
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