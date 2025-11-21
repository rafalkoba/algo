#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define eb emplace_back
#define pb push_back
#define loop(i, a, b) for (int i = a; i < b; i++)
#define rloop(i, a, b) for (int i = a; i >= b; i--)
#define all(x) (x).begin(), (x).end()

void solve()
{
	int n, d;
	ll p;

	cin >> n >> p >> d;

	vll w(n), przykryte(n), pref(n);
	ll suma = 0;

	loop(i, 0, n)
	{
		cin >> w[i];

		suma += w[i];
		if (i >= d)
			suma -= w[i - d];
		przykryte[i] = suma;

		pref[i] += w[i];
		if (i > 0)
			pref[i] += pref[i - 1];
	}

	deque<int> dq;
	dq.push_front(d-1);

	int wyn = d, l = 0;

	for (int r = d; r < n; r++)
	{
		while (!dq.empty() && przykryte[dq.back()] <= przykryte[r])
			dq.pop_back();
		dq.push_back(r);

		if (r - l + 1 <= d)
			continue;

		ll suma_prz = pref[r];
		if (l > 0)
			suma_prz -= pref[l - 1];

		while (r - l + 1 > d && suma_prz - przykryte[dq.front()] > p)
		{
			while (!dq.empty() && dq.front() <= l+d-1)
				dq.pop_front();

			suma_prz -= w[l++];
		}

		wyn = max(r - l + 1, wyn);
	}

	cout << wyn;
}


int main()
{
	cin.tie(0)->sync_with_stdio(false);

	int t=1;
	//cin >> t;
	while (t--)
		solve();

	return 0;
}