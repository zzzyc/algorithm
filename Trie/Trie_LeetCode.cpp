#include <bits/stdc++.h>

class TrieNode {
public:
    char val;
    std::vector<TrieNode*> son;
    bool is_end;
    TrieNode(int _val): val(_val), son(26, nullptr), is_end(false) {}
};

class Trie {
private:
    TrieNode* root;
    
    void dfs_delete(TrieNode*& root) {
        if (root == nullptr) return ;
        
        for (int i = 0; i < 26; ++i) {
            dfs_delete(root->son[i]);
        }
        
        delete root;
        root = nullptr;
    }
    
public:
    Trie() {
        root = new TrieNode(0);
    }
    
    ~Trie() {
        dfs_delete(root);
    }
    
    void insert(std::string word) {
        TrieNode* p = root;
        for (auto c: word) {
            int id = c - 'a';
            if (p->son[id] == nullptr) {
                p->son[id] = new TrieNode(c);
            }
            p = p->son[id];
        }
        p->is_end = true;
    }
    
    bool search(std::string word) {
        TrieNode* p = root;
        for (auto c: word) {
            int id = c - 'a';
            if (p->son[id] == nullptr) {
                return false;
            }
            p = p->son[id];
        }
        return p->is_end;
    }
    
    bool startsWith(std::string prefix) {
        TrieNode* p = root;
        for (auto c: prefix) {
            int id = c - 'a';
            if (p->son[id] == nullptr) {
                return false;
            }
            p = p->son[id];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */