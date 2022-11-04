// 平面最近点对问题 O(nlogn) 
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const double eps = 1e-6;
const double INF = 1e18;

struct Point {
    double x, y;
}p[N];
int n;
int t1[N], t2[N];

bool cmp(const Point& A, const Point& B) {
    if (fabs(A.x - B.x) < eps) return A.y < B.y;
    return A.x < B.x;
}

double distance(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double Get(int l, int r) {
    if (l == r) return INF;
    if (l + 1 == r) return distance(p[l], p[r]);

    int mid = (l + r) >> 1;
    double d1 = Get(l, mid);
    double d2 = Get(mid + 1, r);
    double d = min(d1, d2);

    int k1 = 0, k2 = 0;
    for (int i = l; i <= r; ++i)
        if (fabs(p[i].x - p[mid].x) <= d)
            if (i <= mid) t1[k1++] = i;
            else t2[k2++] = i;

    for (int i = 0; i < k1; ++i)
        for (int j = 0; j < k2; ++j)
            d = min(d, distance(p[t1[i]], p[t2[j]]));

    return d;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;

    sort(p, p + n, [](const Point& A, const Point& B) {
            if (fabs(A.x - B.x) < eps) return A.y < B.y;
            return A.x < B.x;
            });

    cout << fixed << setprecision(4) << Get(0, n - 1) << endl;

    return 0;
}
