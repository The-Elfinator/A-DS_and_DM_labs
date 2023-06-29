#include <bits/stdc++.h>

static const double PI = 3.14159265358979323846;
using namespace std;

typedef complex<double> base;

void transformation(vector<base> & a, bool reversed) {
    int n = (int) a.size();
    if (n == 1) {
        return;
    }
    vector<base> a0 (n/2);
    vector<base> a1 (n/2);
    int j = 0;
    for (int i = 0; i < n; i += 2) {
        a0[j] = a[i];
        a1[j] = a[i+1];
        j++;
    }
    transformation(a0, reversed);
    transformation(a1, reversed);

    double ang = 2*PI/n;
    if (reversed) {
        ang *= -1;
    }
    base w (1);
    base wn (cos(ang), sin(ang));
    for (int i = 0; i < n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (reversed) {
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
        w *= wn;
    }
}

void multiply (const vector<int> &a, const vector<int> &b, vector<int> &res) {
    vector<base> fa (a.begin(), a.end());
    vector<base> fb (b.begin(), b.end());
    int n = 1;
    while (n < max (a.size(), b.size())) {
        n <<= 1;
    }
    n <<= 1;
    fa.resize (n),  fb.resize (n);
    transformation(fa, false);
    transformation(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    transformation(fa, true);
    res.resize (n);
    for (int i=0; i < n; i++) {
        res[i] = int(fa[i].real() + 0.5);
    }
}

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    int sign_a = 0;
    if (a[0] == '-') {
        sign_a = -1;
    } else if (a[0] != '0') {
        sign_a = 1;
    }
    int sign_b = 0;
    if (b[0] == '-') {
        sign_b = -1;
    } else if (b[0] != '0') {
        sign_b = 1;
    }
    if (sign_a == 0 || sign_b == 0) {
        cout << 0 << '\n';
        return 0;
    }
    int sign;
    if (sign_a == sign_b) {
        sign = 1;
    } else {
        sign = -1;
    }
    int begin_a = 0;
    if (sign_a == -1) {
        begin_a = 1;
    }
    int begin_b = 0;
    if (sign_b == -1) {
        begin_b = 1;
    }
    a = a.substr(begin_a);
    b = b.substr(begin_b);
    vector<int> arr1(a.size());
    vector<int> arr2(b.size());
    for (int i = 0; i < a.size(); i++) {
        char c = a[i];
        arr1[a.size() - i - 1] = c - '0';
    }
    for (int i = 0; i < b.size(); i++) {
        char c = b[i];
        arr2[b.size() - i - 1] = c - '0';
    }
    vector<int> res;
    multiply(arr1, arr2, res);
    int shift = 0;
    int last_zero = res.size();
    for (int &d: res) {
        d += shift;
        shift = d / 10;
        d = d % 10;
    }
    for (int i = res.size() - 1; i >= 0; i--) {
        if (res[i] == 0) {
            last_zero = i;
        } else {
            break;
        }
    }
    if (sign == -1) {
        cout << '-';
    }
    for (int i = last_zero - 1; i >= 0; i--) {
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
