#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

struct path {
    vector<int> v;
    int dem, p, ranc;
};

vector<path> paths;

void build(int n, vector<int> & need) {
    paths.resize(n);
    for (int i = 1; i < n; ++i) {
        paths[i].v = {i};
        paths[i].dem = need[i];
        paths[i].p = i;
        paths[i].ranc = 0;
    }
}

int get_root(int u) {
    if (paths[u].p == u) return u;
    return paths[u].p = get_root(paths[u].p);
}

bool check(int u, int v) {
    return get_root(u) == get_root(v);
}

int pathscnt;

void unit(int u, int v, int mcap) {
    u = get_root(u);
    v = get_root(v);
    if (u == v) return;
    if (paths[u].dem + paths[v].dem > mcap) {
        return;
    }
    --pathscnt;
    if (paths[u].ranc < paths[v].ranc) {
        swap(u, v);
    }
    paths[u].dem += paths[v].dem;
    for (auto r : paths[v].v) {
        paths[u].v.push_back(r);
    }
    paths[v].p = u;
    if (paths[u].ranc == paths[v].ranc) {
        ++paths[u].ranc;
    }
}

long double tsp(vector<pair<int, int>> & verts) {
    int n = verts.size();
    vector<long double> x;
    vector<long double> y;
    int iter = 0;
    for (; iter < n; ++iter) {
        auto [xi, yi] = verts[iter];
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
    return fin_ans;
}

int main() {
    int n, m, mcap;
    cin >> n >> m >> mcap;
    pathscnt = n - 1;
    vector<int> need(n);
    vector<pair<int, int>> verts;
    for (int i = 0; i < n; ++i) {
        long double x, y;
        cin >> need[i] >> x >> y;
        verts.push_back({x, y});
    }
    vector<tuple<long double, int, int>> profit;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long double dist1 = hypot(verts[0].first - verts[i].first, verts[0].second - verts[i].second);
            long double dist2 = hypot(verts[0].first - verts[j].first, verts[0].second - verts[j].second);
            long double dist3 = hypot(verts[i].first - verts[j].first, verts[i].second - verts[j].second);
            long double s = dist1 + dist2 - dist3;
            profit.push_back({s, i, j});
        }
    }
    sort(profit.rbegin(), profit.rend());
    build(n, need);
    for (auto [s, i, j] : profit) {
        unit(i, j, mcap);
        if (pathscnt <= m) break;
    }
    vector<bool> checked(n, false);
    long double res = 0;
    for (int i = 1; i < n; ++i) {
        int root = get_root(i);
        if (checked[root]) continue;
        vector<pair<int, int>> tverts;
        tverts.push_back(verts[0]);
        for (auto r : paths[root].v) {
            tverts.push_back(verts[r]);
        }
        res += tsp(tverts);
        checked[root] = true;
    }
    cout << res;
}
