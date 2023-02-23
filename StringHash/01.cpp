/*
    题目：字符串哈希
    题目链接：https://www.acwing.com/problem/content/843/
    题目类型：字符串哈希，快速处理字符串匹配等问题
*/

#include <bits/stdc++.h>
using namespace std;

class StringHash {
private:
    typedef unsigned long long ull;
    static const ull P = 13331;
    static const int N = 100010;
    
    ull p[N];
    ull h[N];

public:

    StringHash() {}
    
    StringHash(const std::string& str) {
        init(str);
    }
    
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
        if(b - a != d - c) return false;
        return get(a, b) == get(c, d);
    }
    
}sh;

int n, m;
string s;
int a, b, c, d;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    cin >> s;
    
    sh.init(s);
    
    while (m--) {
        cin >> a >> b >> c >> d;
        if (sh.check(a, b, c, d)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}