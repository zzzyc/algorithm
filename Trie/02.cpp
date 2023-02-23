#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int BIT = 26;

class Trie {
private:
    int tr[N][BIT];
    int cnt[N];
    int idx;
    
public:
    Trie(): idx(0) {}
    
    void insert(char* s) {
        int p = 0;
        for (; s != nullptr && *s != '\0'; s++) {
            int id = (*s) - 'a';
            if (!tr[p][id]) tr[p][id] = ++idx;
            p = tr[p][id];
        }
        cnt[p] += 1;
    }
    
    int query(char* s) {
        int p = 0;
        for (; s != nullptr && *s != '\0'; s++) {
            int id = (*s) - 'a';
            if (!tr[p][id]) return 0;
            p = tr[p][id];
        }
        return cnt[p];
    }
}trie;


char s[N], op[2];
int m;

int main()
{
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%s%s", op, s);
        if (*op == 'I') trie.insert(s);
        else printf("%d\n", trie.query(s));
    }
    
    return 0;
}