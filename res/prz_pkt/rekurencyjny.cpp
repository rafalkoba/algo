#include <bits/stdc++.h>
using namespace std;

int n;

// Funkcje agregujące
long long sum_op(long long a, long long b) { return a + b; }
long long prod_op(long long a, long long b) { return a * b; }
long long gcd_op(long long a, long long b) { return gcd(a, b); }

struct SegmentTree {
    vector<long long> t;
    vector<long long> a;
    long long (*op)(long long, long long);
    long long neutral;

    SegmentTree(int n_, long long (*op_)(long long,long long), long long neutral_) {
        n = n_;
        a.assign(n, 0);
        t.assign(4*n, neutral_);
        op = op_;
        neutral = neutral_;
    }

    void build(int v, int tl, int tr) {
        if(tl == tr) t[v] = a[tl];
        else {
            int tm = (tl + tr)/2;
            build(2*v, tl, tm);
            build(2*v+1, tm+1, tr);
            t[v] = op(t[2*v], t[2*v+1]);
        }
    }

    void update(int v, int tl, int tr, int pos, long long val) {
        if(tl == tr) t[v] = val;
        else {
            int tm = (tl + tr)/2;
            if(pos <= tm) update(2*v, tl, tm, pos, val);
            else update(2*v+1, tm+1, tr, pos, val);
            t[v] = op(t[2*v], t[2*v+1]);
        }
    }

    long long query(int v, int tl, int tr, int l, int r) {
        if(l > r) return neutral;
        if(l == tl && r == tr) return t[v];
        int tm = (tl + tr)/2;
        return op(query(2*v, tl, tm, l, min(r, tm)),
                  query(2*v+1, tm+1, tr, max(l, tm+1), r));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<long long> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];

    SegmentTree st(n, sum_op, 0); // zmień sum_op na prod_op lub gcd_op w razie potrzeby
    st.a = arr;
    st.build(1,0,n-1);

    cout << st.query(1,0,n-1,0,n-1) << "\n"; // przykład pełnego zapytania
}
