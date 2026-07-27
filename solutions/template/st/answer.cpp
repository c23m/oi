#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vi nextLarger(n, n);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] < arr[i])
        {
            nextLarger[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    for (int i = 0; i < n; i++)
    {
        if (nextLarger[i] == n)
        {
            cout << 0;
        }
        else
        {
            cout << nextLarger[i] + 1;
        }
        cout << ' ';
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

    solve();
    return 0;
}