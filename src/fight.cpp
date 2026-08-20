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

enum Team
{
    none = 0,
    red,
    blue
};

string to_string(Team team)
{
    if (team == red)
        return "red";
    else
        return "blue";
}

int ptoi(Team team, int i)
{
    if (team == red)
        return i - 1;
    else
        return solver.n - i;
}

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

    int reward = 0;
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
        if (team == red)
        {
            solver.redUnits.insert(solver.redUnits.begin(), nullptr);
            solver.redUnits.pop_back();
        }
        else
        {
            solver.blueUnits.insert(solver.blueUnits.begin(), nullptr);
            solver.blueUnits.pop_back();
        }
        if (elements < solver.healths[current])
        {
            return;
        }

        elements -= solver.healths[current];
        Unit *Obj;
        switch (current)
        {
        case dragon:
            Obj = new Dragon(team, ++count);
            break;
        case ninja:
            Obj = new Ninja(team, ++count);
            break;
        case iceman:
            Obj = new Iceman(team, ++count);
            break;
        case lion:
            Obj = new Lion(team, ++count);
            break;
        case wolf:
            Obj = new Wolf(team, ++count);
            break;
        }
        if (team == red)
        {
            solver.redUnits[0] = Obj;
        }
        else
        {
            solver.blueUnits[0] = Obj;
        }
        solver.outputTime();
        Obj->outputInfo();
        cout << "born" << '\n';
    }

    void report()
    {
        solver.outputTime();
        cout << elements << " elements in ";
        cout << to_string(team) << " headquarter" << '\n';
    }
};

class City
{
public:
    Team flag;
    int elements = 0;
    Team lastWin;
    City()
    {
        flag = none;
        lastWin = none;
        elements = 0;
    }
    void countingFlag(int i)
    {
        Team raised = none;
        if (solver.redUnits[i - 1] && solver.redUnits[i - 1]->win)
        {
            if (lastWin != red)
            {
                lastWin = red;
            }
            else if (flag != red)
            {
                raised = red;
            }
        }
        else if (solver.blueUnits[solver.n - i] && solver.blueUnits[solver.n - i]->win)
        {
            if (lastWin != blue)
            {
                lastWin = blue;
            }
            else if (flag != blue)
            {
                raised = blue;
            }
        }
        else if (solver.redUnits[i - 1] && solver.blueUnits[solver.n - i])
        {
            lastWin = none;
        }
        if (raised != none)
        {
            solver.outputTime();
            cout << to_string(raised) << " flag raised in city " << i << '\n';
        }
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

    Unit(Team team, Type type, int id)
        : team(team), elements(solver.healths[type]), force(solver.attacks[type]), id(id)
    {
    }

    virtual void march(int position)
    {
        this->position = position;
        if (position == 0 || position == solver.n + 1)
        {
            solver.outputTime();
            outputInfo();
            cout << "reached ";
            cout << to_string(team);
            cout << " headquarter ";
            outputWith();
            cout << '\n';
            Headquarter &enemyHome = team == red ? solver.redHome : solver.blueHome;
            if (!enemyHome.reached)
            {
                enemyHome.reached = true;
            }
            else
            {
                solver.outputTime();
                cout << to_string(team);
                cout << " headquarter was taken";
                cout << '\n';
                solver.ending = true;
            }
        }
        else
        {
            solver.outputTime();
            outputInfo();
            cout << "marched to city " << position << ' ';
            outputWith();
            cout << '\n';
        }
    }

    virtual void attack(Unit &enemy)
    {

        enemy.elements -= force;
        if (enemy.elements <= 0)
        {
            win = true;
            enemy.dead();
            getElements();
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
            enemy.dead();
            getElements();
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
        cout << '\n';

        if (team == red)
        {
            solver.redUnits[position - 1] = nullptr;
        }
        else
        {
            solver.blueUnits[solver.n - position] = nullptr;
        }
        delete this;
    }

    void getElements()
    {
        if (team == red)
            solver.redHome.reward += solver.citys[position].elements;
        else
            solver.blueHome.reward += solver.citys[position].elements;
        solver.outputTime();
        outputInfo();
        cout << "earned " << solver.citys[position].elements << " elements for his headquarter" << '\n';
        solver.citys[position].elements = 0;
    }

    virtual Type getType() = 0;

    void outputInfo()
    {
        vector<string> types =
            {"dragon", "ninja", "iceman", "lion", "wolf"};
        cout << to_string(team) << ' ' << types[getType()] << ' ' << id << ' ';
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
    Dragon(Team team, int id) : Unit(team, Type::dragon, id)
    {
    }

    void attack(Unit &enemy) override
    {
        enemy.elements -= force;
        if (enemy.elements <= 0)
        {
            win = true;
            enemy.dead();
            yell();
            getElements();
        }
        else
        {
            enemy.fightBack(*this);
        }
    }

    void yell()
    {
        solver.outputTime();
        outputInfo();
        cout << "yelled ";
        outputLocation();
        cout << '\n';
    }

    Type getType() override
    {
        return dragon;
    }
};

class Ninja : public Unit
{
public:
    Ninja(Team team, int id) : Unit(team, Type::ninja, id)
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
    Iceman(Team team, int id) : Unit(team, Type::iceman, id)
    {
    }

    void march(int position) override
    {
        int step = ptoi(team, position) + 1;
        if (step % 2 == 0)
        {
            elements -= 9;
            force += 20;
            if (elements <= 0)
                elements = 1;
        }
        Unit::march(position);
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
    Lion(Team team, int id) : Unit(team, Type::lion, id), originHp(elements)
    {
    }
    void march(int i) override
    {
        Unit::march(i);
        originHp = elements;
    }

    void dead() override
    {
        if (team == red)
        {
            solver.blueUnits[solver.n - position]->elements += originHp;
        }
        else
        {
            solver.redUnits[position - 1]->elements += originHp;
        }
        Unit::dead();
    }

    Type getType() override
    {
        return lion;
    }
};

class Wolf : public Unit
{

public:
    int winTimes = 0;
    Wolf(Team team, int id) : Unit(team, Type::wolf, id)
    {
    }

    void attack(Unit &enemy) override
    {

        enemy.elements -= force;
        if (enemy.elements <= 0)
        {
            win = true;
            winTimes++;
            if (winTimes % 2 == 0)
            {
                force *= 2;
                elements *= 2;
            }
            enemy.dead();
        }
        else
        {
            enemy.fightBack(*this);
        }
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

    vector<Unit *> redUnits;
    vector<Unit *> blueUnits;

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
        redUnits.assign(n + 1, nullptr);
        blueUnits.assign(n + 1, nullptr);
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
        while (!ending)
        {
            switch (minute)
            {
            case 0:
                redHome.spawn();
                blueHome.spawn();
                break;
            case 10:
                for (int i = 0; i <= n + 1; i++)
                {
                    if (i - 1 >= 0 && redUnits[i - 1])
                    {
                        redUnits[i - 1]->march(i);
                    }
                    if (n - i >= 0 && blueUnits[n - i])
                    {
                        blueUnits[n - i]->march(i);
                    }
                }
                if (ending)
                    return;
                break;
            case 20:
                for (int i = 1; i <= n; i++)
                {
                    citys[i].elements += 10;
                }
                break;
            case 30:
                for (int i = 1; i <= n; i++)
                {
                    if (redUnits[i - 1] && !blueUnits[n - i])
                    {
                        redUnits[i - 1]->getElements();
                        redHome.elements += redHome.reward;
                        redHome.reward = 0;
                    }
                    if (blueUnits[n - i] && !redUnits[i - 1])
                    {
                        blueUnits[n - i]->getElements();
                        blueHome.elements += blueHome.reward;
                        blueHome.reward = 0;
                    }
                }
                break;
            case 40:
                for (int i = 1; i <= n; i++)
                {
                    if (!redUnits[i - 1] || !blueUnits[n - i])
                    {
                        continue;
                    }
                    if (citys[i].flag == red || (citys[i].flag == none && i % 2 == 1))
                    {
                        redUnits[i - 1]->attack(*blueUnits[n - i]);
                    }
                    else
                    {
                        blueUnits[n - i]->attack(*redUnits[i - 1]);
                    }
                    citys[i].countingFlag(i);
                }
                for (int i = n - 1; i >= 0; i--)
                {
                    if (redUnits[i] && redUnits[i]->win)
                    {
                        if (redHome.elements >= 8)
                        {
                            redHome.elements -= 8;
                            redUnits[i]->elements += 8;
                        }
                        else
                        {
                            redUnits[i]->elements += redHome.elements;
                            redHome.elements = 0;
                        }
                    }
                    if (blueUnits[i] && blueUnits[i]->win)
                    {
                        if (blueHome.elements >= 8)
                        {
                            blueHome.elements -= 8;
                            blueUnits[i]->elements += 8;
                        }
                        else
                        {
                            blueUnits[i]->elements += blueHome.elements;
                            blueHome.elements = 0;
                        }
                    }
                    redHome.elements += redHome.reward;
                    redHome.reward = 0;
                    blueHome.elements += blueHome.reward;
                    blueHome.reward = 0;
                }
                break;
            case 50:
                redHome.report();
                blueHome.report();
                break;
            }
            nextTime();
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