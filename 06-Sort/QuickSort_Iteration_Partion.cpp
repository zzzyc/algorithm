/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/787/
    题目类型：迭代版本的快速排序
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int a[N], n;

int partition(int a[], int l, int r) {
    int x = a[l + r >> 1];
    int i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    return j;
}

void quick_sort(int a[], int l, int r) {
    if (l >= r) return ;
    
    stack<pair<int, int>> stk;
    stk.push(make_pair(l, r));
    while (!stk.empty()) {
        int L = stk.top().first, R = stk.top().second;
        stk.pop();

        int j = partition(a, L, R);
        if (j > L) stk.push(make_pair(L, j));
        if (j + 1 < R) stk.push(make_pair(j + 1, R));
    }
}

/*
栈使用数组模拟实现
pair<int, int> stk[N];
int top;
void quick_sort_array(int a[], int l, int r) {
    if (l >= r) return ;
    
    top = 0;
    stk[++top] = make_pair(l, r);
    while (top > 0) {
        int L = stk[top].first, R = stk[top].second;
        top -= 1;

        int j = partition(a, L, R);
        if (j > L) stk[++top] = make_pair(L, j);
        if (j + 1 < R) stk[++top] = make_pair(j + 1, R);
    }
}
*/

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    quick_sort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d%c", a[i], " \n"[i + 1 == n]);

    return 0;
}