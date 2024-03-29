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
    
    void removeLRUNodeFromHashTable(LRUNode* node) {
        if (!key2LRUNode.count(node->key)) return;
        key2LRUNode.erase(node->key);
    }

    void insertLRUNodeToHashTable(LRUNode* node) {
        key2LRUNode[node->key] = node;
    }

    void removeLRUNodeFromLinklist(LRUNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertLRUNodeToLinklist(LRUNode* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

public:

    LRUCache(int capacity): capacity_(capacity) {
        size_ = 0;
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
            delete cur;
            cur = next;
        }
        delete cur;
    }
    
    int get(int key) {
        // key 不存在
        if (!key2LRUNode.count(key)) return -1;
        
        // 取出 key 对应的 LRUNode
        LRUNode* node = key2LRUNode[key];
        
        // 当前 LRUNode 是最近一次使用的，将其放到链表头
        removeLRUNodeFromLinklist(node);
        insertLRUNodeToLinklist(node);
        return node->val;
    }
    
    void put(int key, int value) {
        // 如果不存在 key ，则需要新建该键值对
        if (!key2LRUNode.count(key)) {
            // 缓存已满，要从缓存中通过LRU策略弹出最近最少使用的LRUNode
            if (size_ >= capacity_) {
                // 链表尾即最近最少使用的
                LRUNode* node = tail->prev;
                // 从链表中删去
                removeLRUNodeFromLinklist(node);
                // 从哈希表中删去
                removeLRUNodeFromHashTable(node);
                // 释放 node 的内存空间，如果是智能指针就不需要手动释放了
                delete node;
                // 释放一个空间
                size_ -= 1;
            }
            // 创建一个新的 LRUNode
            LRUNode* newLRUNode = new LRUNode(key, value);
            // 添加到链表中
            insertLRUNodeToLinklist(newLRUNode);
            // 添加到哈希表中
            insertLRUNodeToHashTable(newLRUNode);
            size_ += 1;

        } else {
            // 获取到 key 对应的已存在于缓存中的 LRUNode 节点
            LRUNode* node = key2LRUNode[key];
            // 更新键值对的权值
            node->val = value;
            // 从链表中删去
            removeLRUNodeFromLinklist(node);
            // 添加到链表中
            insertLRUNodeToLinklist(node);
            // 添加到哈希表中，其实这步是不需要的，因为哈希表对应的是 LRUNode 的地址
            insertLRUNodeToHashTable(node);
            // 这里只是 key 对应的 value 修改了，故 size_ 不变
        }
    }

private:
    int size_;
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