#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

void solve()
{
    double S, C, L, P0, ans;
    int N;
    cin >> S >> C >> L >> P0 >> N;
    vector<double> cost(N + 2, 0);   // 起点到此站的耗油量
    vector<double> price(N + 2, -1); // 当前油价
    price[0] = P0;
    cost[N + 1] = S / L;
    for (int i = 1; i <= N; i++)
    {
        double d;
        cin >> d >> price[i];
        cost[i] = d / L;
    }

    vector<int> nextcheaper(N + 2, N + 1);
    vector<int> st;
    for (int i = N + 1; i >= 0; i--)
    {
        while (!st.empty() && price[st.back()] >= price[i])
            st.pop_back();
        if (!st.empty())
            nextcheaper[i] = st.back();
        st.push_back(i);
    }

    double rest = 0; // 存下来的油
    int cur = 0;     // 当前加油站
    while (cur < N + 1)
    {
        if (cost[nextcheaper[cur]] - cost[cur] <= C)
        {
            ans += (cost[nextcheaper[cur]] - cost[cur] - rest) * price[cur];
            rest = 0;
            cur = nextcheaper[cur];
        }
        else
        {
            double minprice = 501;
            int mins = cur;
            for (int i = cur + 1; i < N + 1; i++)
            {
                if (cost[i] - cost[cur] > C)
                {
                    break;
                }
                if (price[i] <= minprice)
                {
                    mins = i;
                    minprice = price[i];
                }
            }
            if (mins == cur)
            {
                cout << "No Solution";
                return;
            }
            ans += (C - rest) * price[cur];
            rest = C - (cost[mins] - cost[cur]);
            cur = mins;
        }
    }

    cout << fixed << setprecision(2) << ans;
}
int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}