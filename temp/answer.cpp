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
    int n, m;
    cin >> n >> m;
    int LOG = log2(n) + 2;
    vvi f(n + 1, vi(LOG));
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
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        int len = log2(r - l + 1);
        cout << max(f[l][len], f[r - (1 << len) + 1][len]) << '\n';
    }
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
    // cin >> t;
    while (t--)
        solve();
    return 0;
}