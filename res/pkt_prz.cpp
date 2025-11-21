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

int baza = 1;
vll t, w;

void buduj(int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = w[tl - 1];
    else
    {
        int tm = (tl + tr) / 2;
        buduj(v * 2, tl, tm);
        buduj(v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

void akt(int v, int tl, int tr, int poz, ll c)
{
    if (tl == tr)
        t[v] = c;
    else
    {
        int tm = (tl + tr) / 2;
        if (poz <= tm)
            akt(v * 2, tl, tm, poz, c);
        else
            akt(v * 2 + 1, tm + 1, tr, poz, c);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

ll query(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return t[v];

    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, min(r, tm)) + query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
}
int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int n, q;

    cin >> n >> q;

    while (baza <= n)
        baza <<= 1;

    t.resize(2 * baza);
    w.resize(n);

    loop(i, 0, n)
        cin >> w[i];

    buduj(1, 1, n);

    while (q--)
    {
        int k, a, b;
        cin >> k >> a >> b;

        if (k == 1)
            akt(1, 1, n, a, b);
        else
            cout << query(1, 1, n, a, b) << '\n';
    }
    return 0;
}