#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    cout << fixed << setprecision(10);
    int n;
    cin >> n;
    vector<long double> x;
    vector<long double> y;
    int iter = 0;
    for (; iter < n; ++iter) {
        long double xi, yi;
        cin >> xi >> yi;
        x.push_back(xi);
        y.push_back(yi);
    }
    vector<int> ans(n);
    for (iter = 0; iter < n; ++iter) {
        ans[iter] = iter;
    }
    for (iter = 1; iter < n; ++iter) {
        long double minimum = pow(10, 17);
        int need = iter;
        for (int v = iter; v < n; ++v) {
            long double dist = sqrt(pow(x[ans[iter - 1]] - x[ans[v]], 2) + pow(y[ans[iter - 1]] - y[ans[v]], 2));
            if (dist < minimum) {
                minimum = dist;
                need = v;
            }
        }
        int c = ans[iter];
        ans[iter] = ans[need];
        ans[need] = c;
    }
    long double fin_ans = 0;
    for (iter = 0; iter < n; ++iter) {
        int next = (iter + 1) % n;
        long double dist1 = pow(x[ans[iter]] - x[ans[next]], 2);
        long double dist2 = pow(y[ans[iter]] - y[ans[next]], 2);
        fin_ans = fin_ans + sqrt(dist1 + dist2);
    }
    cout << fin_ans << '\n';
}
