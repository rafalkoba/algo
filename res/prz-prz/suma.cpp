#include <bits/stdc++.h>
#include <random>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define eb emplace_back
#define pb push_back
#define loop(i, a, b) for (int i = a; i < b; i++)
#define rloop(i, a, b) for (int i = a; i >= b; i--)
#define all(x) (x).begin(), (x).end()

vll t, a, lazy;

void push(int v, int l, int r)
{
    if (lazy[v] != 0)
    {
        t[v] += (r - l + 1) * lazy[v];
        if (l != r)
        {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void buduj(int v, int l, int r)
{
    if (l == r)
        t[v] = a[l];
    else
    {
        int m = (l + r) / 2;
        buduj(v * 2, l, m);
        buduj(v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

void akt(int v, int tl, int tr, int l, int r, int c)
{
    push(v, tl, tr);
    if (tl > r || tr < l) return;
    
    if (tl >= l && tr <= r)
    {
        lazy[v] += c;
        push(v, tl, tr);
        return;
    }

    int tm = (tl + tr) / 2;
    akt(v * 2, tl, tm, l, r, c);
    akt(v * 2 + 1, tm+1, tr, l, r, c);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

ll pytaj(int v, int tl, int tr, int l, int r)
{
    push(v, tl, tr);
    if (tl > r || tr < l) return 0;
    if (tl >= l && tr <= r) return t[v];

    int tm = (tl + tr) / 2;
    return pytaj(v * 2, tl, tm, l, r) + pytaj(v * 2 + 1, tm + 1, tr, l, r);
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, m, rodz, l, r, wart;

    cin >> n >> m;

    t.resize(4 * n); lazy.resize(4 * n); a.resize(n+1);
    
    loop(i, 1, n + 1) cin >> a[i];

    buduj(1, 1, n);

    while (m--)
    {
        cin >> rodz;
        if (rodz == 1)
        {
            cin >> l >> r;
            cout << pytaj(1, 1, n, l, r) << '\n';
        }
        else
        {
            cin >> l >> r >> wart;
            akt(1, 1, n, l, r, wart);
        }
    }
    return 0;
}