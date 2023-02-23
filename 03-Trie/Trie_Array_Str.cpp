/*
    由于是数组实现，注意开成全局变量
    主要适用于字符串统计问题
*/
#include <bits/stdc++.h>

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