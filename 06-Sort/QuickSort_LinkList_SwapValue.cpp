/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/1453/
    题目类型：链表版本的快速排序
    
    备注：递归法，仅交换节点的值
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

class Solution {
private:
    ListNode* quickSortList(ListNode* head) {
        if (!head) return head;
        quickSort(head, NULL);
        return head;
    }

    void quickSort(ListNode* head, ListNode* tail) {
        if (head == tail || head->next == tail) return ;

        int key = head->val;
        ListNode *p = head, *q = p->next;
        while (q != tail) {
            if (q->val < key) {
                p = p->next;
                swap(p->val, q->val);
            }
            q = q->next;
        }
        if (p != head)
            swap(head->val, p->val);

        quickSort(head, p);
        quickSort(p->next, tail);
    }
public:
    ListNode* sortList(ListNode* head) {
        return quickSortList(head);
    }
};


int main()
{
    // int arr[] = {2, 1};
    // int n = sizeof(arr) / sizeof(arr[0]);

    int n, num;
    ListNode* preHead = new ListNode(-1);
    ListNode* temp = preHead;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num);
        temp->next = new ListNode(num);
        temp = temp->next;
    }
    
    Solution x;
    ListNode* ansNode = x.sortList(preHead->next);

    while (ansNode != nullptr) cout << ansNode->val << " ", ansNode = ansNode->next;
    cout << "\n";

    return 0;
}