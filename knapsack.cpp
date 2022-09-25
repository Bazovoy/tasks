#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cost;
    vector<int> weight;
    int iter = 0;
    for (; iter < n; ++iter) {
        int p, w;
        cin >> p >> w;
        cost.push_back(p);
        weight.push_back(w);
    }
    vector<int> ans(m + 1);
    iter = 0;
    for (; iter < n; ++iter) {
        for (int j = m; j - weight[iter] >= 0; --j) {
            if (ans[j - weight[iter]] + cost[iter] > ans[j]) {
                ans[j] = ans[j - weight[iter]] + cost[iter];
            }
        }
    }
    cout << ans[m] << '\n';
}
