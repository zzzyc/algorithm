// https://leetcode.cn/problems/lru-cache/description/
/*
    LRUCache 需要有两个哨兵标记头尾
    get 需要将 LRUNode 更新到最近一次使用的位置
    put 需要考虑 capacity ，如果不够则需要弹出 LRUNode，然后将新插入的 LRUNode 更新到最近一次使用的位置
    考虑到内存泄露，在 ~LRUCache 中需要释放所有的 LRUNode，包括 head 和 tail
*/
class LRUCache {
private:
    struct LRUNode {
        LRUNode* prev;
        LRUNode* next;
        int key;
        int val;
        LRUNode(int key, int val): key(key), val(val), prev(nullptr), next(nullptr) {}
    };
    
    void deleteLRUNode(LRUNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertLRUNode(LRUNode* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

public:

    LRUCache(int capacity): capacity_(capacity) {
        head = new LRUNode(-1, -1);
        tail = new LRUNode(-2, -1);
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    }

    ~LRUCache() {
        LRUNode* cur = head->next;
        while (cur != head) {
            LRUNode* next = cur->next;
            // key2LRUNode.erase(cur->key);
            delete cur;
            cur = next;
        }
        // key2LRUNode.erase(cur->key);
        delete cur;
    }
    
    int get(int key) {
        // 没找到
        if (!key2LRUNode.count(key)) return -1;
        // 存在，那么获取值，并且更新其位置
        LRUNode* node = key2LRUNode[key];
        deleteLRUNode(node);
        insertLRUNode(node);
        return node->val;
    }
    
    void put(int key, int value) {
        // 不存在，考虑 capacity 是否足够
        if (!key2LRUNode.count(key)) {
            // capacity 为 0，需要删除一个
            if (capacity_ == 0) {
                LRUNode* node = tail->prev;
                // 从链表中删除
                deleteLRUNode(node);
                // 从哈希表中删除
                key2LRUNode.erase(node->key);
                // 释放内存
                delete node;
                // capacity + 1 
                capacity_ += 1;
            }
            // 创建新 LRUNode
            LRUNode* newLRUNode = new LRUNode(key, value);
            // 插入到哈希表中
            key2LRUNode[key] = newLRUNode;
            // 插入到链表中
            insertLRUNode(newLRUNode);

            // capacity - 1
            capacity_ -= 1;

        } else {
            LRUNode* node = key2LRUNode[key];
            
            // 从链表中删除旧的
            deleteLRUNode(node);
            
            // 修改为新的 LRUNode
            node->val = value;

            // 直接覆盖哈希表中原来的 key 对应的 LRUNode
            key2LRUNode[key] = node;

            // 插入链表
            insertLRUNode(node);

            // capacity 不变
        }
    }

private:
    int capacity_;
    unordered_map<int, LRUNode*> key2LRUNode;
    LRUNode* head;
    LRUNode* tail;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */