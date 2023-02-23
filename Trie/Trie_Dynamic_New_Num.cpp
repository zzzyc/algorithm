/*
    Vector版本
*/
#include <bits/stdc++.h>

struct TrieNode {

    // 根据需要调整，要么是二进制 2，要么是字母字符集 26 或 52
    static const int N = 2;

    std::vector<TrieNode*> son;
    bool exist;
    int count;

    TrieNode(): son(N, nullptr), exist(false), count(0) {}
};

class Trie {
private:
    TrieNode* root;
    static const int MAXBIT = 30;

public:
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int x) {
        TrieNode* p = root;
        for (int i = MAXBIT; i >= 0; --i) {
            p->count += 1;
            int id = x >> i & 1;
            if (p->son[id] == nullptr) p->son[id] = new TrieNode();
            p = p->son[id];
        }
        p->count += 1;
    }

    int query(int x) {
        TrieNode* p = root;
        int res = 0;
        for (int i = MAXBIT; i >= 0; --i) {
            int id = x >> i & 1;
            if (p->son[id ^ 1] != nullptr) {
                if (id ^ 1) res |= 1 << i;
                p = p->son[id ^ 1];
            } else {
                if (id) res |= 1 << i;
                p = p->son[id];
            }
        }
        return res;
    }

};