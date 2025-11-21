#include <bits/stdc++.h>
using namespace std;

long long sum_op(long long a, long long b) { return a + b; }
long long prod_op(long long a, long long b) { return a * b; }
long long gcd_op(long long a, long long b) { return gcd(a,b); }

struct SegmentTreeIter {
    int n;
    vector<long long> t;
    long long (*op)(long long,long long);
    long long neutral;

    SegmentTreeIter(int n_, long long (*op_)(long long,long long), long long neutral_) {
        n = n_;
        t.assign(2*n, neutral_);
        op = op_;
        neutral = neutral_;
    }

    void build(vector<long long> &a) {
        for(int i=0;i<n;i++) t[n+i] = a[i];
        for(int i=n-1;i>0;i--) t[i] = op(t[2*i], t[2*i+1]);
    }

    void update(int pos, long long val) {
        pos += n;
        t[pos] = val;
        for(pos/=2; pos>0; pos/=2) t[pos] = op(t[2*pos], t[2*pos+1]);
    }

    long long query(int l, int r) {
        l += n; r += n;
        long long res = neutral;
        while(l <= r) {
            if(l%2==1) res = op(res, t[l++]);
            if(r%2==0) res = op(res, t[r--]);
            l/=2; r/=2;
        }
        return res;
    }
};

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    SegmentTreeIter st(n, sum_op, 0);
    st.build(a);
    cout << st.query(0,n-1) << "\n";
}
