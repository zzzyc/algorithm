/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/789/
    题目类型：链表版本的快速排序
    
    备注：由于快速排序最坏是 O(n^2) 的，而链表中选择 pivot 的时间过长，所以在最坏情况下很慢
         故本题在上述给定的题目的时间限制下是无法通过的。
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

/*
    递归法，将小于 pivot ，等于 pivot 和大于 pivot 的三个部分，分别列一个链表
    然后递归
        小于 pivot 的部分 
        大于 pivot 的部分
    最后将三者链接起来即可。
*/
class Solution {
private:
    ListNode* getTail(ListNode* node) {
        while (node->next) node = node->next;
        return node;
    }

public:

    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;

        ListNode* L = new ListNode(-1);
        ListNode* M = new ListNode(-1);
        ListNode* R = new ListNode(-1);

        ListNode* tL = L;
        ListNode* tM = M;
        ListNode* tR = R;
        int val = head->val;

        while (head != nullptr) {
            if (head->val < val) {
                tL->next = head;
                tL = tL->next;
            } else if (head->val > val) {
                tR->next = head;
                tR = tR->next;
            } else {
                tM->next = head;
                tM = tM->next;
            }
            head = head->next;
        }
        tL->next = nullptr;
        tM->next = nullptr;
        tR->next = nullptr;
        
        
        L->next = sortList(L->next);
        R->next = sortList(R->next);

        getTail(L)->next = M->next;
        tM->next = R->next;

        ListNode* ansHead = L->next;
        delete L;
        delete M;
        delete R;

        return ansHead;
    }
};

/*
    递归法，仅交换节点的值
*/
class Solution2 {
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


/*
    交换节点
*/
class Solution3 {
private:
    ListNode* quickSortList(ListNode* head) {
        quickSort(head, nullptr);
        return head;
    }

    void swapListNode(ListNode*& preA, ListNode*& preB) {
        if (preA == preB) return ;
        ListNode* A = preA->next;
        ListNode* B = preB->next;
        if (A->next == B) {
            A->next = B->next;
            B->next = A;
            preB->next = A;
            preA = A;
        } else if (B->next == A) {
            B->next = A->next;
            A->next = B;
            preA->next = B;
            preB = B;
        } else {
            swap(A->next, B->next);
            preA->next = B;
            preB->next = A;
        }
    }

    void quickSort(ListNode* head, ListNode* tail) {
        if (head == tail || head->next == tail) return ;

        int key = head->val;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* preP = dummy, *preQ = head;
        ListNode *p = head, *q = p->next;
        while (preQ->next != tail) {
            if (preQ->next->val < key) {
                preP = preP->next;
                swapListNode(preP, preQ);
            } 
            preQ = preQ->next;
        }
        if (preP->next != head)
            swapListNode(preP, dummy);
        
        delete dummy;

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
    
    Solution2 x;
    // Solution3 x;
    ListNode* ansNode = x.sortList(preHead->next);

    while (ansNode != nullptr) cout << ansNode->val << " ", ansNode = ansNode->next;
    cout << "\n";

    return 0;
}