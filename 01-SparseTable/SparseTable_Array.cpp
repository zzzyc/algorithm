/*
    数组版本 ST 表，因为一般的空间复杂度为 O(nlogn)
    所以使用时不要开在栈上，开成全局变量
*/

#include <bits/stdc++.h>
class SparseTable {
private:
    static const int BIT = 20;
    static const int N = 200010;
    int f[BIT][N];
    int lg[N];

    int n;
    std::function<int(int,int)> comp;

public:

    SparseTable(std::function<int(int,int)> comp = [](int a, int b) {return std::max(a, b);}, int n = N - 1): n(n), comp(comp) {}

    void init(int n = N - 1) {
        lg[1] = 0;
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
    }

    void build(const int a[], int n) {
        for (int i = 1; i <= n; ++i) f[0][i] = a[i];
        for (int i = 1; i < BIT; ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                f[i][j] = comp(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
    }

    int query(int l, int r) {
        if (l > r) std::swap(l, r);
        int bit = lg[r - l + 1];
        return comp(f[bit][l], f[bit][r - (1 << bit) + 1]);
    }
};