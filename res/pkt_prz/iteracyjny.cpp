#include <bits/stdc++.h>
using namespace std;

struct BITIter {
    int n;
    vector<long long> t;

    BITIter(int n_) {
        n = n_;
        t.assign(2*n, 0);
    }

    void build(const vector<long long> &a) {
        for(int i=0;i<n;i++) t[n+i] = a[i];
        for(int i=n-1;i>0;i--) t[i] = t[2*i] + t[2*i+1];
    }

    // punktowa aktualizacja
    void update(int pos, long long val) {
        pos += n;
        t[pos] = val;
        for(pos /= 2; pos > 0; pos /= 2)
            t[pos] = t[2*pos] + t[2*pos+1];
    }

    // suma na przedziale [l..r]
    long long query(int l, int r) {
        l += n; r += n;
        long long res = 0;
        while(l <= r) {
            if(l%2==1) res += t[l++];
            if(r%2==0) res += t[r--];
            l /= 2; r /= 2;
        }
        return res;
    }
};

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    BITIter bit(n);
    bit.build(a);

    cout << bit.query(0,n-1) << "\n"; // suma całego zakresu
}
