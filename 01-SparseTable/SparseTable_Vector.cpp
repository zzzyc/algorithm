/*
    vector版本 ST 表
*/

#include <bits/stdc++.h>
class SparseTable {
private:
    static const int BIT = 20;
    static const int N = 200010;
    std::vector<std::vector<int>> f;
    std::vector<int> lg;
    int n;
    int maxbit;

    std::function<int(int,int)> comp;

public:

    // 默认情况下是返回区间最大值
    SparseTable(std::function<int(int,int)> comp = [](int a, int b) {return std::max(a, b);}, int n = N - 1): n(n), maxbit(0), comp(comp) {}

    void init(int len = N - 1) {
        n = len;

        lg = std::vector<int>(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

        maxbit = lg[n];

        f = std::vector<std::vector<int>>(maxbit + 1, std::vector<int>(n + 1));
    }

    // index 从 1 开始
    void build(const int a[], int n) {
        init(n);
        for (int i = 1; i <= n; ++i) f[0][i] = a[i];
        for (int i = 1; i <= maxbit; ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                f[i][j] = comp(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
    }

    int query(int l, int r) {
        if (l > r) std::swap(l, r);
        int bit = lg[r - l + 1];
        return comp(f[bit][l], f[bit][r - (1 << bit) + 1]);
    }
};