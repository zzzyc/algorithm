/*
    题目：快速排序
    题目链接：https://www.acwing.com/problem/content/1453/
    题目类型：链表版本的快速排序
    
    备注：
        递归法，将小于 pivot ，等于 pivot 和大于 pivot 的三个部分，分别列一个链表
        然后递归
            小于 pivot 的部分 
            大于 pivot 的部分
        这两部分即可

        最后将三者链接起来即可。
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