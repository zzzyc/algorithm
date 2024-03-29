/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/787/
    题目类型：递归版本的快速排序
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int a[N], n;

void quick_sort(int a[], int l, int r) {
    if (l >= r) return ;
    int x = a[l + r >> 1];
    int i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    quick_sort(a, l, j);
    quick_sort(a, j + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    quick_sort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d%c", a[i], " \n"[i + 1 == n]);

    return 0;
}