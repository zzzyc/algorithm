/*
    题目：归并排序
    题目链接：https://www.acwing.com/problem/content/789/
    题目类型：迭代版本的归并排序
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int a[N], n;

int t[N];
void merge_sort_iter_do_while(int a[], int l, int r) {
    int m = r - l + 1;
    for (int len = 1; len < m; len *= 2) {
        int curi = l, lasti = l + len;
        int curj = l + len, lastj = min(curj + len, r + 1);

        do {
            int start = curi;
            int g = 0;
            while (curi < lasti && curj < lastj) {
                if (a[curi] > a[curj]) {
                    t[g++] = a[curj++];
                } else {
                    t[g++] = a[curi++];
                }
            }

            while (curi < lasti) t[g++] = a[curi++];
            while (curj < lastj) t[g++] = a[curj++];

            for (int x = start, y = 0; y < g; ++x, ++y) a[x] = t[y];

            // 最后需要合并的部分如果只剩一块，其实是可以不用考虑的
            curi = lastj;
            lasti = curi + len;
            curj = lasti;
            lastj = min(curj + len, r + 1);

        } while (curj <= r);
    }
}

int b[N];
void merge_sort_iter_for(int l, int r) {
    int n = r - l + 1;
    for (int step = 1; step < n; step <<= 1) {
        for (int i = l, k = 1; i + step <= n; i += step * 2) {
            int li = i, lj = i + step;
            int ri = li + step - 1, rj = min(lj + step - 1, r);
            while (li <= ri && lj <= rj) {
                if (a[li] <= a[lj]) b[k] = a[li], li += 1;
                else b[k] = a[lj], lj += 1;
                k += 1;
            }

            while (li <= ri) b[k] = a[li], li += 1, k += 1;
            while (lj <= rj) b[k] = a[lj], lj += 1, k += 1;
        }
        for (int i = l, j = 1; i <= r; ++i, ++j) a[i] = b[j];
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int  i = 0; i < n; ++i) scanf("%d", &a[i]);
    merge_sort_iter_do_while(a, 0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d%c", a[i], " \n"[i + 1 == n]);

    return 0;
}