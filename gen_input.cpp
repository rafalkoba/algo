#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ===========================
    // PARAMETRY GENEROWANEGO TESTU
    // ===========================

    int n = rnd(5, 20);         // liczba wierzchołków
    int m = rnd(0, n * (n - 1) / 4);   // liczba krawędzi grafu
    int seqN = rnd(5, 20);      // długość ciągu

    // ===========================
    // 1. GENERACJA CIĄGU LICZB
    // ===========================

    vector<int> seq(seqN);
    for (int i = 0; i < seqN; i++) seq[i] = rnd(-50, 50);

    // ===========================
    // 2. GENERACJA DRZEWA
    // ===========================

    vector<pair<int,int>> tree;
    for (int i = 2; i <= n; i++) {
        int parent = rnd(1, i - 1);
        tree.push_back({parent, i});
    }

    // ===========================
    // 3. GENERACJA GRAFU NIESKIEROWANEGO
    // ===========================

    set<pair<int,int>> edges;

    while ((int)edges.size() < m) {
        int a = rnd(1, n);
        int b = rnd(1, n);
        if (a == b) continue;
        if (a > b) swap(a, b);
        edges.insert({a, b});
    }

    // ===========================
    // WYJŚCIE (dowolny format)
    // ===========================
    // Tu wypisuję:
    // n
    // ciąg
    // n-1 krawędzi drzewa
    // m krawędzi grafu

    cout << "SEQ " << seqN << "\n";
    for (int x : seq) cout << x << " ";
    cout << "\n";

    cout << "TREE " << n << "\n";
    for (auto [a,b] : tree) {
        cout << a << " " << b << "\n";
    }

    cout << "GRAPH " << n << " " << m << "\n";
    for (auto [a,b] : edges) {
        cout << a << " " << b << "\n";
    }

    return 0;
}
