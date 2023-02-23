/*
    题目：食物链
    题目链接：https://www.acwing.com/problem/content/description/242/
    题目类型：带权并查集 or 种类并查集的经典例题
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 150010;
// 种类并查集
// x 吃 y，说明 x 和 y + n 是同类；x 被 y 吃，说明 x 和 y + n * 2 是同类
// y + n 是 x 的猎物，y + 2 * n 是 x 的天敌
int p[N]; 
int n, k;
int d, x, y;

int find(int x) {
    int root = x;
    while (root != p[root]) root = p[root];
    while (x != p[x]) {
        int nx = p[x];
        p[x] = root;
        x = nx;
    }
    return root;
}

void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) p[a] = b;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n * 3; ++i) p[i] = i;

    int ans = 0;
    while (k--) {
        scanf("%d%d%d", &d, &x, &y);
        if (x > n || y > n) {
            ans += 1;
            continue ;
        }
        if (d == 1) {
            if (find(x) == find(y + n) || find(x) == find(y + n * 2)) {
                ans += 1;
                continue ;
            }
            merge(x, y);
            merge(x + n, y + n);
            merge(x + 2 * n, y + 2 * n);
        } else {
            if (x == y) {
                ans += 1;
                continue ;
            } else {
                // x 吃 y
                if (find(x) == find(y) || find(x) == find(y + n * 2)) {
                    ans += 1;
                    continue ;
                } else {
                    merge(x, y + n);
                    merge(x + n, y + 2 * n);
                    merge(x + 2 * n, y);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}