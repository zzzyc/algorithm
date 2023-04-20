/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/1453/
    题目类型：链表版本的快速排序
    
    备注：
        单链表的原地快排，核心在于如何交换两个节点
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* quickSortList(ListNode* head) {
        return quickSort(head, nullptr);
    }

private:
    void swapListNode(ListNode*& preP, ListNode*& preQ) {
        if (preP == preQ) return ;

        if (preP->next != preQ) {
            ListNode* p = preP->next;
            ListNode* q = preQ->next;

            ListNode* qnxt = q->next;
            q->next = p->next;
            p->next = qnxt;
            preP->next = q;
            preQ->next = p;
        } else {
            ListNode* p = preP->next;
            ListNode* q = preQ->next;

            ListNode* qnxt = q->next;
            q->next = p;
            p->next = qnxt;
            preP->next = q;
            preQ = q;
        }
    }

    ListNode* quickSort(ListNode* head, ListNode* tail) {
        if (head == tail || head->next == tail) return head;

        int key = head->val;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        // 如此是保证 [p + 1, q - 1] 都是小于 key 的
        ListNode* preP = dummy, *preQ = head;
        while (preQ->next != tail) {
            if (preQ->next->val < key) {
                preP = preP->next;
                swapListNode(preP, preQ);
            }
            preQ = preQ->next;
        }

        /*
            1. 如果此时 preP->next == head
            要保证 [p + 1, q - 1] 都是大于 key 的，而后面不存在比 key 小的，那么切换成
            [preP->next->next, tail] ，[head, preP->next] 长度为 1，且比后面的值都小，无需操作

            2. 如果此时 preP->next != head
            说明 [head->next, preP] 都是小于 key 的
            我们需要使得前半段都是小于 key 的，那么拿 preP->next 与 head 交换即可

         */


        if (preP->next != head) {
            swapListNode(dummy, preP);
        }

        ListNode* mid = preP->next;
        dummy->next = quickSort(dummy->next, mid);
        mid->next = quickSort(mid->next, tail);

        return dummy->next;
    }
};

int main()
{
    Solution x;

    int arr[] = {5, 3, 2};
//    int arr[] = {2, 1};
    int n = sizeof(arr) / (sizeof(arr[0]));

    ListNode* dummy = new ListNode(-1);
    ListNode* temp = dummy;
    for (int i = 0; i < n; ++i) {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }

    ListNode* ans = x.quickSortList(dummy->next);

    for (ListNode* p = ans; p != nullptr; p = p->next) {
        cout << p->val << " \n"[p->next == nullptr];
    }

    return 0;
}