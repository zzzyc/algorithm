/*
    题目：归并排序
    题目链接：https://www.acwing.com/problem/content/789/
    题目类型：链表的自顶向下（递归）和自底向上（迭代）的归并排序
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

// 自底向上
class Solution {
private:
    ListNode* getTail(ListNode* node, int len) {
        while (len > 0 && node != nullptr) node = node->next, len -= 1;
        return node;
    }
public:

    ListNode* sortList(ListNode* head) {
        int n = 0;
        ListNode* temp = head;
        while (temp != nullptr) n += 1, temp = temp->next;
        
        ListNode mynode(-1);
        ListNode* dummy = &mynode;
        for (int len = 1; len < n; len *= 2) {
            ListNode* curL = head;
            ListNode* lastL = getTail(curL, len);

            ListNode* curR = lastL;
            ListNode* lastR = getTail(curR, len);

            dummy->next = nullptr;
            ListNode* temp = dummy;
            do {
                while (curL != lastL && curR != lastR) {
                    if (curL->val <= curR->val) {
                        ListNode* nxt = curL->next;
                        curL->next = nullptr;
                        temp->next = curL;
                        curL = nxt;
                    } else {
                        ListNode* nxt = curR->next;
                        curR->next = nullptr;
                        temp->next = curR;
                        curR = nxt;
                    }
                    temp = temp->next;
                }

                while (curL != lastL) {
                    ListNode* nxt = curL->next;
                    curL->next = nullptr;
                    temp->next = curL;
                    curL = nxt;
                    temp = temp->next;
                }

                while (curR != lastR) {
                    ListNode* nxt = curR->next;
                    curR->next = nullptr;
                    temp->next = curR;
                    curR = nxt;
                    temp = temp->next;
                }

                curL = lastR;
                lastL = getTail(curL, len);
                
                curR = lastL;
                lastR = getTail(curR, len);
            } while (curL != nullptr);

            head = dummy->next;
        }
        return head;
    }
};

// 自顶向下
class Solution2 {
private:
    // 确定中间节点
    ListNode* split(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* second = slow->next;
        slow->next = nullptr;
        return second;
    }

    // 合并排序链表
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->val < head2->val) {
                cur->next = head1;
                head1 = head1->next;
            }
            else {
                cur->next = head2;
                head2 = head2->next;
            }

            cur = cur->next;
        }
        cur->next = (head1 == nullptr) ? head2 : head1;

        ListNode* ret = dummy->next;
        delete dummy;
        dummy = nullptr;
        return ret;
    }

public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* head1 = head;
        ListNode* head2 = split(head);

        head1 = sortList(head1);
        head2 = sortList(head2);

        return merge(head1, head2);
    }
};

int main()
{
    // Solution x;
    Solution2 x;
    
    ListNode* dummy = new ListNode(-1);
    ListNode* temp = dummy;
    
    int n, num;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &num);
        temp->next = new ListNode(num);
        temp = temp->next;
    }
    
    ListNode* ansHead = x.sortList(dummy->next);
    while (ansHead != nullptr) {
        printf("%d%c", ansHead->val, " \n"[ansHead->next == nullptr]);
        ansHead = ansHead->next;
    }
    return 0;
}