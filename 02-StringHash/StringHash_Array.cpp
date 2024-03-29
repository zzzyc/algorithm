/*
    本题是数组实现形式，注意使用时 class StringHash 的对象需要开在全局
    因为这类使用 64 位整数的运算相对较慢，因此这里不再提供 vector 版本
*/
#include <bits/stdc++.h>

class StringHash {
private:
    typedef unsigned long long ull;
    // 使用时记得修改对应的大小和模数
    static const ull P = 13331;
    static const int N = 100010;
    
    ull p[N];
    ull h[N];

public:

    StringHash() {}
    
    void init(const std::string& str) {
        int n = int(str.size()) + 1;
        p[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p[i] = p[i - 1] * P;
            h[i] = h[i - 1] * P + str[i - 1];
        }
    }
    
    ull get(int a, int b) {
        return h[b] - h[a - 1] * p[b - a + 1];
    }
    
    bool check(int a, int b, int c, int d) {
        return (b - a == d - c) && get(a, b) == get(c, d);
    }
    
};
