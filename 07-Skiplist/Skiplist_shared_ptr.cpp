#include <vector>
#include <memory>
#include <iostream>

typedef int KeyType;
typedef int ValueType;

struct SkiplistNode {
    KeyType key_;
    ValueType value_;
    std::vector<std::shared_ptr<SkiplistNode>> next_;
    SkiplistNode(int key, int value, int level): key_(key), value_(value), next_(level, nullptr) {}
    ~SkiplistNode() {}
};

class MySkiplist {

public:
    MySkiplist();
    ~MySkiplist() {}
    std::shared_ptr<SkiplistNode> createSkiplistNode(int level, const KeyType& key, const ValueType& value);
    bool insert(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key, const ValueType& value);
    bool search(const KeyType& key, const ValueType& value);

private:
    static int getRandomLevel();
    void findPrevPerLevel(const KeyType& keyType, std::vector<std::shared_ptr<SkiplistNode>>& prev) const;

public:
    int level_;
    std::shared_ptr<SkiplistNode> header_;

    static constexpr uint32_t kMaxLevel = 16;
};

MySkiplist::MySkiplist(): level_(kMaxLevel), header_(createSkiplistNode(kMaxLevel, -1, -1)) {}

std::shared_ptr<SkiplistNode> MySkiplist::createSkiplistNode(int level,
                                                             const KeyType &key,
                                                             const ValueType &value) {
    return std::make_shared<SkiplistNode>(SkiplistNode(key, value, level));
}

bool MySkiplist::insert(const KeyType& key, const ValueType& value) {
    std::vector<std::shared_ptr<SkiplistNode>> prev(kMaxLevel);
    findPrevPerLevel(key, prev);

    // key 已存在
    auto temp = prev[0]->next_[0];

    auto p = createSkiplistNode(kMaxLevel, key, value);
    int curLevel = getRandomLevel();
    for (int i = 0; i < curLevel; ++i) {
        p->next_[i] = prev[i]->next_[i];
        prev[i]->next_[i] = p;
    }
    return true;
}

bool MySkiplist::erase(const KeyType& key, const ValueType& value) {
    std::vector<std::shared_ptr<SkiplistNode>> prev(kMaxLevel);
    findPrevPerLevel(key, prev);

    // key 不存在
    auto p = prev[0]->next_[0];
    if (p == nullptr || p->key_ != key) return false;

    for (int i = 0; i < level_ && prev[i]->next_[i] == p; ++i) {
        prev[i]->next_[i] = p->next_[i];
    }

    return true;
}

bool MySkiplist::search(const KeyType& key, const ValueType& value) {
    std::vector<std::shared_ptr<SkiplistNode>> prev(kMaxLevel);
    findPrevPerLevel(key, prev);

    auto p = prev[0]->next_[0];
    return p != nullptr && p->key_ == key;
}

void MySkiplist::findPrevPerLevel(const KeyType& key, std::vector<std::shared_ptr<SkiplistNode>>& prev) const {
    auto p = header_;
    for (int i = level_ - 1; i >= 0; --i) {
        while (p->next_[i] && p->next_[i]->key_ < key) p = p->next_[i];
        prev[i] = p;
    }
}

int MySkiplist::getRandomLevel() {
    int randomLevel = 1;
    while (randomLevel < kMaxLevel && rand() % 2 == 1) randomLevel += 1;
    return randomLevel;
}

class Skiplist {
public:
    std::shared_ptr<MySkiplist> mySkiplist;
    Skiplist() {
        mySkiplist = std::make_shared<MySkiplist>(MySkiplist());
    }

    bool search(int target) {
        return mySkiplist->search(target, target);
    }

    void add(int num) {
        mySkiplist->insert(num, num);
    }

    bool erase(int num) {
        return mySkiplist->erase(num, num);
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */