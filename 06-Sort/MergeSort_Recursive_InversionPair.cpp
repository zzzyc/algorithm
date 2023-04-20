/*
    题目：归并排序求逆序对
    题目链接：https://www.acwing.com/problem/content/789/
    题目类型：递归版本的归并排序求逆序对
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int a[N], n;

long long ans;
int t[N];
void merge_sort(int a[], int l, int r) {
    if (l >= r) return ;
    int mid = l + r >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);

    int i = l, j = mid + 1, g = 0;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            t[g++] = a[j++];
            ans += mid - i + 1;
        } else {
            t[g++] = a[i++];
        }
    }
    
    while (i <= mid) t[g++] = a[i++];
    while (j <= r) t[g++] = a[j++];

    for (int x = l, y = 0; y < g; ++x, ++y) a[x] = t[y];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    
    ans = 0;
    merge_sort(a, 0, n - 1);
    
    printf("%lld\n", ans);

    return 0;
}