/*
    对于每个 count ，一个链表，这个链表是 LRU 的
    对于整体，是一个单调递增的链表，表示 count 和其对应的 LRU 链表

    1. 先来看 LRU 链表，这里只需要 put 和 del 即可，可以直接套用 LRUCache
    2. 再来看 LFU 的哈希表 key2LFUNode，cnt2LRUCache
    3. 再来看 LFU 维护的一个单调递增的链表

*/

#include <bits/stdc++.h>
using namespace std;

struct LRUNode {
    LRUNode* prev;
    LRUNode* next;
    int key;
    int val;
    int cnt;
    LRUNode(int key, int val): key(key), val(val), cnt(1), prev(nullptr), next(nullptr) {}
};

void removeLRUNodeFromLinklist(LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertLRUNodeToLinklist(LRUNode* node, LRUNode* head) {
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
}

class LRUCache {
    void removeLRUNodeFromHashTable(LRUNode* node) {
        if (!key2LRUNode.count(node->key)) return;
        key2LRUNode.erase(node->key);
    }

    void insertLRUNodeToHashTable(LRUNode* node) {
        key2LRUNode[node->key] = node;
    }
public:
    LRUCache() {
        size_ = 0;
        head = new LRUNode(-1, -1);
        tail = new LRUNode(-2, -1);
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    }

    void put(int key, int value) {
        if (!key2LRUNode.count(key)) {
            LRUNode* newLRUNode = new LRUNode(key, value);
            insertLRUNodeToLinklist(newLRUNode, head);
            insertLRUNodeToHashTable(newLRUNode);
            size_ += 1;
        } else {
            LRUNode* node = key2LRUNode[key];
            node->val = value;
            removeLRUNodeFromLinklist(node);
            insertLRUNodeToLinklist(node, head);
            insertLRUNodeToHashTable(node);
        }
    }

    void del(int key) {
        if (!key2LRUNode.count(key)) return;
        auto node = key2LRUNode[key];
        removeLRUNodeFromLinklist(node);
        removeLRUNodeFromHashTable(node);
        size_ -= 1;
    }

    LRUNode* pop() {
        if (empty()) return nullptr;
        LRUNode* node = tail->prev;
        del(node->key);
        return node;
    }

    bool empty() const  {
        return size_ == 0;
    }

private:
    int size_;
    unordered_map<int, LRUNode*> key2LRUNode;
    LRUNode* head;
    LRUNode* tail;
};


struct IncNode {
    int key;                // key, 对应的次数
    IncNode* prev;
    IncNode* next;
    LRUCache* lru;
    IncNode(int key): key(key), prev(nullptr), next(nullptr), lru(new LRUCache()) {}
};

void removeIncNodeFromLinklist(IncNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertIncNodeFromLinklist(IncNode* node, IncNode* head) {
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
}

class LFUCache {
private:
    void removeIncNodeFromHashTable(IncNode* node) {
        if (!cnt2IncNode.count(node->key)) return;
        cnt2IncNode.erase(node->key);
    }

    void insertIncNodeToHashTable(IncNode* node) {
        cnt2IncNode[node->key] = node;
    }

    void removeLRUNodeFromHashTable(LRUNode* node) {
        if (!key2LRUNode.count(node->key)) return;
        key2LRUNode.erase(node->key);
    }

    void insertLRUNodeToHashTable(LRUNode* node) {
        key2LRUNode[node->key] = node;
    }

public:
    LFUCache(int capacity) {
        capacity_ = capacity;
        size_ = 0;
        head = new IncNode(0);
        tail = new IncNode(-1);
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    }

    int get(int key) {
        // 如果不存在当前 key ，直接返回 -1
        if (!key2LRUNode.count(key)) return -1;

        // 找到 key 对应的 LRUNode，value 就是 node->val
        LRUNode* node = key2LRUNode[key];
        int ans = node->val;

        // 找到 LRUNode 对应的 IncNode
        IncNode* cur = cnt2IncNode[node->cnt];
        // 为插入 node 到新的一层的前一个节点做准备
        IncNode* pre = cur->prev;

        LRUCache* lru = cur->lru;
        // 将 LRUNode 从 IncNode 对应的 lru 中移除
        lru->del(node->key);
        if (lru->empty()) {
            // 如果 lru 为空，将 cur 这个 IncNode 移除
            removeIncNodeFromHashTable(cur);
            removeIncNodeFromLinklist(cur);
        } else {
            // 如果 cur 对应的 lru 移除 node 后不为空，则 node 新到的计数 IncNode 的前一个就是 cur
            pre = cur;
        }

        // 添加到新的 lru 中
        node->cnt += 1;
        IncNode* incNode;
        // 如果新的 lru 不存在，就创建
        if (!cnt2IncNode.count(node->cnt)) {
            incNode = new IncNode(node->cnt);
            incNode->lru->put(node->key, node->val);
            insertIncNodeFromLinklist(incNode, pre);
        } else {
            incNode = cnt2IncNode[node->cnt];
            incNode->lru->put(node->key, node->val);
        }
        insertIncNodeToHashTable(incNode);

        return ans;
    }

    void put(int key, int value) {
        if (!key2LRUNode.count(key)) {
            if (size_ >= capacity_) {
                IncNode* incNode = head->next;
                LRUNode* lruNode = incNode->lru->pop();
                removeLRUNodeFromHashTable(lruNode);
                size_ -= 1;
            }
            LRUNode* node = new LRUNode(key, value);
            // 如果新的 lru 不存在，就创建

            IncNode* incNode;
            // 不存在计数为 1 的 IncNode，创建
            if (!cnt2IncNode.count(node->cnt)) {
                incNode = new IncNode(node->cnt);
                incNode->lru->put(node->key, node->val);
                // 将这个 IncNode 添加到 IncNode 对应的链表中
                insertIncNodeFromLinklist(incNode, head);
            } else {
                incNode = cnt2IncNode[node->cnt];
                incNode->lru->put(node->key, node->val);
            }
            insertIncNodeToHashTable(incNode);
            insertLRUNodeToHashTable(node);
            size_ += 1;
        } else {
            LRUNode* node = key2LRUNode[key];
            node->val = value;

            IncNode* cur = cnt2IncNode[node->cnt];
            IncNode* pre = cur->prev;

            LRUCache* lru = cur->lru;
            // 从当前 lru 中删除
            lru->del(node->key);
            // 如果 lru 为空，说明要合并了，先找到前后的两个
            if (lru->empty()) {
                removeIncNodeFromHashTable(cur);
                removeIncNodeFromLinklist(cur);
            } else {
                pre = cur;
            }

            IncNode* incNode;
            // 添加到新的 lru 中
            node->cnt += 1;
            // 如果新的 lru 不存在，就创建
            if (!cnt2IncNode.count(node->cnt)) {
                incNode = new IncNode(node->cnt);
                incNode->lru->put(node->key, node->val);
                insertIncNodeFromLinklist(incNode, pre);
                cnt2IncNode[node->cnt] = incNode;
            } else {
                incNode = cnt2IncNode[node->cnt];
                incNode->lru->put(node->key, node->val);
            }
            insertIncNodeToHashTable(incNode);
            insertLRUNodeToHashTable(node);
        }
    }

private:
    int size_;
    int capacity_;
    IncNode* head;
    IncNode* tail;
    unordered_map<int, LRUNode*> key2LRUNode;
    unordered_map<int, IncNode*> cnt2IncNode;
};



int main()
{
    LFUCache* lfu = new LFUCache(2);

    lfu->put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu->put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    cout << lfu->get(1) << endl;      // 返回 1
    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu->put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
    // cache=[3,1], cnt(3)=1, cnt(1)=2
    cout << lfu->get(2) << endl;      // 返回 -1（未找到）
    cout << lfu->get(3) << endl;      // 返回 3
    // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu->put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
    // cache=[4,3], cnt(4)=1, cnt(3)=2
    cout << lfu->get(1) << endl;      // 返回 -1（未找到）
    cout << lfu->get(3) << endl;      // 返回 3
    // cache=[3,4], cnt(4)=1, cnt(3)=3
    cout << lfu->get(4) << endl;      // 返回 4
    // cache=[3,4], cnt(4)=2, cnt(3)=3

    return 0;
}

