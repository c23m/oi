```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct mint
{
    static const int MOD = 998244353;
    int val;

    mint(long long val = 0)
    {
        if (val < 0)
            val = val % MOD + MOD;
        if (val >= MOD)
            val %= MOD;
        this->val = val;
    }

    mint pow(long long n) const
    {
        mint res = 1;
        mint a = *this;
        while (n)
        {
            if (n & 1)
                res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

    mint inv() const
    {
        return pow(MOD - 2);
    }

    mint &operator+=(const mint &b)
    {
        val += b.val;
        if (val >= MOD)
            val -= MOD;
        return *this;
    }

    mint &operator-=(const mint &b)
    {
        val -= b.val;
        if (val < 0)
            val += MOD;
        return *this;
    }

    mint &operator*=(const mint &b)
    {
        val = (long long)val * b.val % MOD;
        return *this;
    }

    mint &operator/=(const mint &b)
    {
        return *this *= b.inv();
    }

    friend mint operator+(mint a, const mint &b)
    {
        return a += b;
    }

    friend mint operator-(mint a, const mint &b)
    {
        return a -= b;
    }

    friend mint operator*(mint a, const mint &b)
    {
        return a *= b;
    }

    friend mint operator/(mint a, const mint &b)
    {
        return a /= b;
    }

    friend mint operator+(long long a, const mint &b)
    {
        return mint(a) + b;
    }

    friend mint operator-(long long a, const mint &b)
    {
        return mint(a) - b;
    }

    friend mint operator*(long long a, const mint &b)
    {
        return mint(a) * b;
    }

    friend mint operator/(long long a, const mint &b)
    {
        return mint(a) / b;
    }

    friend istream &operator>>(istream &in, mint &a)
    {
        long long val;
        in >> val;
        a = mint(val);
        return in;
    }

    friend ostream &operator<<(ostream &out, const mint &a)
    {
        return out << a.val;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.rbegin(), a.rend());
    mint ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += a[i] * (mint(3).pow(n - 1 - i) + 1) / 2 * mint(2).pow(i);
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```