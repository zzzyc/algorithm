// https://leetcode.cn/problems/lfu-cache/description/
/*
    对于 LFU 来说，其多了一个 count 的概念
    即每个 Node 每被使用一次，使用次数加 1 ，每次去除使用次数最少的，当有多个使用次数最少的，再使用 LRU

    这么来看，LFU 是一层对 LRU 的封装

    每个使用次数构成一个链表，这个链表是 LRU 的
    然后有一个 LFU 中 使用次数构成的链表，所以每个使用次数需要对应一个链表
*/

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