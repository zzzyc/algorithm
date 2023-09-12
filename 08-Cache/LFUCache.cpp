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

void deleteLRUNode(LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertLRUNode(LRUNode* node, LRUNode* head) {
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
}

class LRUCache {

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

    ~LRUCache() {
    }

    void put(int key, int value) {
        if (!key2LRUNode.count(key)) {
            LRUNode* newLRUNode = new LRUNode(key, value);
            insertLRUNode(newLRUNode, head);
            key2LRUNode[key] = newLRUNode;
            size_ += 1;
        } else {
            LRUNode* node = key2LRUNode[key];
            deleteLRUNode(node);
            node->val = value;
            key2LRUNode[key] = node;
            insertLRUNode(node, head);
        }
    }

    void del(int key) {
        if (!key2LRUNode.count(key)) return;
        auto node = key2LRUNode[key];
        deleteLRUNode(node);
        key2LRUNode.erase(node->key);
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

    LRUNode* getLRUNode(int key) {
        if (key2LRUNode.count(key)) {
            return key2LRUNode[key];
        }
        return nullptr;
    }

private:
    int size_;
    unordered_map<int, LRUNode*> key2LRUNode;
    LRUNode* head;
    LRUNode* tail;
};


struct IncNode {
    int key;                // key, 对应的个数
    IncNode* prev;
    IncNode* next;
    LRUCache* lru;
    IncNode(int key): key(key), prev(nullptr), next(nullptr), lru(new LRUCache()) {}
};

void deleteIncNode(IncNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertIncNode(IncNode* node, IncNode* head) {
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
}

class LFUCache {

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
        if (!key2LRUNode.count(key)) return -1;
        LRUNode* node = key2LRUNode[key];
        int ans = node->val;

        IncNode* cur = cnt2IncNode[node->cnt];
        IncNode* pre = cur->prev;

        LRUCache* lru = cur->lru;
        // 从当前 lru 中删除
        lru->del(node->key);
        // 如果 lru 为空，说明要合并了，先找到前后的两个
        if (lru->empty()) {
            cnt2IncNode.erase(cur->key);
            deleteIncNode(cur);
        } else {
            pre = cur;
        }

        // 添加到新的 lru 中
        node->cnt += 1;
        IncNode* incNode = nullptr;
        // 如果新的 lru 不存在，就创建
        if (!cnt2IncNode.count(node->cnt)) {
            incNode = new IncNode(node->cnt);
            incNode->lru->put(node->key, node->val);
            insertIncNode(incNode, pre);
        } else {
            incNode = cnt2IncNode[node->cnt];
            incNode->lru->put(node->key, node->val);
        }
        cnt2IncNode[node->cnt] = incNode;

        return ans;
    }

    void put(int key, int value) {
        if (!key2LRUNode.count(key)) {
            if (size_ >= capacity_) {
                IncNode* incNode = head->next;
                LRUNode* lruNode = incNode->lru->pop();
                key2LRUNode.erase(lruNode->key);
                size_ -= 1;
            }
            LRUNode* node = new LRUNode(key, value);
            // 如果新的 lru 不存在，就创建
            if (!cnt2IncNode.count(node->cnt)) {
                IncNode* incNode = new IncNode(node->cnt);
                incNode->lru->put(node->key, node->val);
                insertIncNode(incNode, head);
                cnt2IncNode[node->cnt] = incNode;
            } else {
                IncNode* incNode = cnt2IncNode[node->cnt];
                incNode->lru->put(node->key, node->val);
            }
            key2LRUNode[key] = node;
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
                cnt2IncNode.erase(cur->key);
                deleteIncNode(cur);
            } else {
                pre = cur;
            }

            // 添加到新的 lru 中
            node->cnt += 1;
            // 如果新的 lru 不存在，就创建
            if (!cnt2IncNode.count(node->cnt)) {
                IncNode* incNode = new IncNode(node->cnt);
                incNode->lru->put(node->key, node->val);
                insertIncNode(incNode, pre);
                cnt2IncNode[node->cnt] = incNode;
            } else {
                IncNode* incNode = cnt2IncNode[node->cnt];
                incNode->lru->put(node->key, node->val);
            }
            key2LRUNode[key] = node;
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