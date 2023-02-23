/*
    题目：Trie字符串统计
    题目链接：https://www.acwing.com/problem/content/description/837/
    题目类型：Trie 统计字符串问题
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int BIT = 30;

class Trie {
private:
    int tr[N * BIT][2];
    int idx;

public:
    
    Trie(): idx(0) {}
    
    void insert(int x) {
        int p = 0;
        for (int i = BIT; i >= 0; --i) {
            int id = x >> i & 1;
            if (!tr[p][id]) tr[p][id] = ++idx;
            p = tr[p][id];
        }
    }

    int query(int x) {
        int p = 0;
        int res = 0;
        for (int i = BIT; i >= 0; --i) {
            int id = x >> i & 1;
            if (tr[p][id ^ 1]) {
                if (id ^ 1) res |= 1 << i;
                p = tr[p][id ^ 1];
            } else {
                if (id) res |= 1 << i;
                p = tr[p][id];
            }
        }
        return res;
    }

}trie;

int main()
{
    int n, x;
    scanf("%d", &n);
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        trie.insert(x);
        ans = max(ans, trie.query(x) ^ x);
    }
    
    printf("%d\n", ans);
    return 0;
}