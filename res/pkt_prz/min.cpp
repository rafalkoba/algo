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

int n;

vi tab, t;

void buduj(int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = tab[tl];
    else
    {
        int tm = (tl + tr) / 2;
        buduj(2 * v, tl, tm);
        buduj(2 * v + 1, tm + 1, tr);
        t[v] = min(t[v * 2],t[v * 2 + 1]);
    }
}
void akt(int v, int tl, int tr, int poz, int c)
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

        t[v] = min(t[v * 2], t[v * 2 + 1]);
    }
}

int query(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 2e9;

    if (l == tl && r == tr)
        return t[v];

    int tm = (tl + tr) / 2;

    return min(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    int m, a, b, c, d;

    cin >> n >> m;

    tab.resize(n + 1);
    t.resize(4 * n, 2e9);

    loop(i, 1, n + 1)
        cin >> tab[i];

    buduj(1, 1, n);

    while (m--)
    {
        cin >> a >> b >> c;
        if (a == 1)
            akt(1, 1, n, b, c);
        else
            cout << query(1, 1, n, b, c) << '\n';
    }
    //cout << query(1,1,n,1,4);
    return 0;
}