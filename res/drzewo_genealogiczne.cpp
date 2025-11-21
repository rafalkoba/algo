#include <bits/stdc++.h>

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

const ll modulo = (ll)1e18 + 37;
ll ksor;

inline ll polacz(ll a, ll b)
{
    a ^= ksor;
    b ^= ksor;
    return ((__int128_t)a * b) % modulo;
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    srand(time(0));
    ksor = rand();
    int n, q, rodz, indeks;
    char c;

    cin >> n >> q;

    vector<vll> hashe(2, vll(1 << (n + 1)));
    int dl = (1 << n);

    loop(i, 0, dl)
    {
        cin >> c;
        hashe[0][dl + i] = (ll)c - 'a';
    }
    loop(i, 0, dl)
    {
        cin >> c;
        hashe[1][dl + i] = (ll)c - 'a';
    }
    loop(i, 0, 2)
    {
        rloop(j, dl - 1, 1)
        {
            hashe[i][j] = polacz(hashe[i][j * 2], hashe[i][j * 2 + 1]);
        }
    }

    cout << (hashe[0][1] == hashe[1][1] ? "TAK\n" : "NIE\n");

    while (q--)
    {
        cin >> rodz >> indeks >> c;
        rodz--;

        hashe[rodz][indeks + dl - 1] = (ll)c - 'a';

        indeks = (indeks + dl - 1) / 2;

        while (indeks >= 1)
        {
            hashe[rodz][indeks] = polacz(hashe[rodz][indeks * 2], hashe[rodz][indeks * 2 + 1]);
            indeks >>= 1;
        }

        cout << (hashe[0][1] == hashe[1][1] ? "TAK\n" : "NIE\n");
    }
    return 0;
}