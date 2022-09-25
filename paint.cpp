#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> cnt;

bool comp(int u, int v) {
    return cnt[v] < cnt[u];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> order;
    int iter = 0;
    while (iter < n) {
        order.push_back(iter);
        ++iter;
    }
    cnt.assign(n, 0);
    vector<vector<bool>> graph(n, vector<bool> (n, false));
    for (iter = 0; iter < m; ++iter) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = true;
        ++cnt[u];
        ++cnt[v];
    }
    vector<int> color(n);
    int c = 1;
    sort(order.begin(), order.end(), comp);
    while (true) {
        bool flag = true;
        for (iter = 0; iter < n; ++iter) {
            if (color[iter] == 0) {
                flag = false;
            }
        }
        if (flag) {
            cout << c - 1;
            return 0;
        }
        vector<int> cn;
        for (auto u : order) {
            if (color[u] == 0) {
                bool nl = true;
                for (auto v : cn) {
                    if (graph[iter][v] != 0) {
                        nl = false;
                        break;
                    }
                }
                if (nl) {
                    color[iter] = c;
                    cn.push_back(iter);
                }
            }
        }
        c++;
    }
}
