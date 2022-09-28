#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int iter = 0;
    vector<tuple<long double, int, int>> order;
    for (; iter < n; ++iter) {
        int p, w;
        cin >> p >> w;
        order.push_back({(long double) w / (long double) p, w, p});
    }
    int ans = 0;
    int wm = 0;
    sort(order.begin(), order.end());
    for (auto [k, w, p] : order) {
        if (wm + w <= m) {
            wm += w;
            ans += p;
        }
    }
    cout << ans << '\n';
}
