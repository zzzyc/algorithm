#include <vector>

class Skiplist {
private:
    // 经验值，可根据实际应用场景动态调整
    static constexpr int level = 8;

    struct SkiplistNode {
        int val;
        // next[i] 表示当前这个结点在第 i 层的下一个结点
        std::vector<SkiplistNode*> next;
        explicit SkiplistNode(int val): val(val) {
            next.resize(level, nullptr);
        }
    }*head;

    // pre[i] 是指在第 i 层，值小于 target 这个结点的前一个结点
    void find(int target, std::vector<SkiplistNode*>& pre) {
        auto p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->next[i] && p->next[i]->val < target) p = p->next[i];
            pre[i] = p;
        }
    }

public:
    Skiplist() {
        // 一个哨兵结点，应该比 Skiplist 中所有的元素都小
        // 一个更为通用的做法是， SkiplistNode 有 val 和 flag 两个属性，flag 用来标识当前结点是否为哨兵
        head = new SkiplistNode(-1);
    }

    ~Skiplist() {
        // 释放整个 Skiplist 的内存，所有结点都必然出现在最底层，所以直接删除最底层即可
        SkiplistNode* temp = head->next[0];
        while (temp) {
            SkiplistNode* nxt = temp->next[0];
            delete temp;
            temp = nxt;
        }
        delete head;
    }

    bool search(int target) {
        // 找到小于 target 的最大的结点
        std::vector<SkiplistNode*> pre(level);
        find(target, pre);

        // 小于 target 的最大结点必然是最底层 target 的前一个结点
        auto p = pre[0]->next[0];
        return p && p->val == target;
    }

    void add(int num) {
        // 找到小于 num 的最大的结点
        std::vector<SkiplistNode*> pre(level);
        find(num, pre);

        // 创建值为 num 的这个结点
        auto p = new SkiplistNode(num);

        // 从最底层开始，以 1/2 的概率往所有 level 层上依次添加
        for (int i = 0; i < level; ++i) {
            p->next[i] = pre[i]->next[i];
            pre[i]->next[i] = p;
            // 如果随机到奇数，则不再添加，直接退出
            if (rand() % 2) break;
        }
    }

    bool erase(int num) {
        // 找到小于 num 的最大的结点
        std::vector<SkiplistNode*> pre(level);
        find(num, pre);

        // 小于 target 的最大结点必然是最底层 target 的前一个结点
        auto p = pre[0]->next[0];
        // 如果最底层 target 的前一个结点 p 不存在或者 p 的值和 num 不相等，则说明 num 不存在于 Skiplist
        if (!p || p->val != num) return false;

        // 从最底层往上依次删除，如果 pre[i]->next[i] != p ，说明第 i 层到第 level-1 层都没有结点 p 了
        for (int i = 0; i < level && pre[i]->next[i] == p; ++i) {
            pre[i]->next[i] = p->next[i];
        }

        // 释放当前删除元素的内存
        delete p;

        return true;
    }
};
