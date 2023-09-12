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

    void removeLRUNodeFromHashTable(LRUNode* node) {
        if (!key2LRUNode.count(node->key)) return;
        key2LRUNode.erase(node->key);
    }

    void insertLRUNodeToHashTable(LRUNode* node) {
        key2LRUNode[node->key] = node;
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
        if (!key2LRUNode.count(key)) return -1;
        LRUNode* node = key2LRUNode[key];
        
        removeLRUNodeFromLinklist(node);
        insertLRUNodeToLinklist(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (!key2LRUNode.count(key)) {
            if (size_ >= capacity_) {
                LRUNode* node = tail->prev;
                removeLRUNodeFromLinklist(node);
                removeLRUNodeFromHashTable(node);
                delete node;
                size_ -= 1;
            }
            LRUNode* newLRUNode = new LRUNode(key, value);
            insertLRUNodeToLinklist(newLRUNode);
            insertLRUNodeToHashTable(newLRUNode);
            size_ += 1;

        } else {
            LRUNode* node = key2LRUNode[key];
            node->val = value;
            removeLRUNodeFromLinklist(node);
            insertLRUNodeToLinklist(node);
            insertLRUNodeToHashTable(node);
        }
    }

private:
    int size_;
    int capacity_;
    unordered_map<int, LRUNode*> key2LRUNode;
    LRUNode* head;
    LRUNode* tail;
};

 int main()
 {
    LRUCache* lRUCache  = new LRUCache(2);
    lRUCache->put(1, 1); // 缓存是 {1=1}
    lRUCache->put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache->get(1);    // 返回 1
    lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache->get(2);    // 返回 -1 (未找到)
    lRUCache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache->get(1);    // 返回 -1 (未找到)
    lRUCache->get(3);    // 返回 3
    lRUCache->get(4);    // 返回 4

    return 0;
 }