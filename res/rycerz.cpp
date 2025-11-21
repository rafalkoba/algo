#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define loop(a, b) for (int i = a; i < b; i++)

vector<pair<int, vector<int>>> G[10 * 1000 + 5];

int n, d, k;

vector<int> wyn(k + 1, 0);

bool odw[10 * 1000 + 5][(1 << 10) + 5];
//czy jest możliwa taka kombinacja mieczy
bool BFS(int ilMieczy)
{
    queue<pair<int, int>> q;

    q.push({ 1, 0 });

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= (1<<ilMieczy); j++)
            odw[i][j] = false;

    int doceloweMiecze = (1 << ilMieczy) - 1;

    int dni = 0;

    while (!q.empty() && dni <= d)
    {
        int ilWOdOdl = q.size();
        for (int wierzcholkiOOdl = 0; wierzcholkiOOdl < ilWOdOdl; wierzcholkiOOdl++)
        {
            int miasto = q.front().first;
            int maska = q.front().second;

            q.pop();



            if (miasto == n && maska == doceloweMiecze)
                return true;

            for (int i = 0; i < G[miasto].size(); i++)
            {
                int nowaMaska = maska;

                for (int j = 0; j < ilMieczy; j++)
                    if (G[miasto][i].second[j] >= wyn[j + 1])
                        nowaMaska |= (1 << j);

                if (!odw[G[miasto][i].first][nowaMaska])
                {
                    odw[G[miasto][i].first][nowaMaska] = true;
                    q.push({ G[miasto][i].first, nowaMaska });
                }
            }
        }
        dni++;
    }

    return false;
}

int main()
{
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);

    int m, a, b, c;

    cin >> n >> m >> d >> k;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        vector<int> miecze(k);

        for (int j = 0; j < k; j++)
            cin >> miecze[j];

        G[a].push_back({ b, miecze });
        G[b].push_back({ a, miecze });
    }

    for (int i = 1; i <= k; i++)
    {
        int l = 0, p = 1000000001, s;
        int w = 0;

        while (l <= p)
        {
            s = (l + p) / 2;

            wyn[i] = s;
            if (BFS(i))
            {
                l = s + 1;
                w = s;
            }
            else
                p = s - 1;
        }

        wyn[i] = w;
    }

    for (int i = 1; i <= k; i++)
        cout << wyn[i] << ' ';

    return 0;
}