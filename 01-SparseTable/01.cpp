/*
    题目：天才的记忆
    题目链接：https://www.acwing.com/problem/content/description/1275/
    题目类型：ST 表，快速查询区间极值
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int a[N];
int n, Q;

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

    SparseTable(std::function<int(int,int)> comp = [](int a, int b) {return a > b;}): n(n), maxbit(0), comp(comp) {}

    void init(int len = N - 1) {
        n = len;

        lg = std::vector<int>(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

        maxbit = lg[n];

        f = std::vector<std::vector<int>>(maxbit + 1, std::vector<int>(n + 1));
    }

    void build(int a[], int n) {
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

int main()
{

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    
    SparseTable st([](int a, int b) {return std::max(a, b);});
    st.build(a, n);
    
    scanf("%d", &Q);
    while (Q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", st.query(l, r));
    }
    
    return 0;
}