/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* fast = head;   //設置快慢指針,n是倒過來數的,我們可以安排快的先跑過n的部分,那剩下的部分一起跟慢指針移動,最後到達終點
    struct ListNode* slow = head;   //讓慢的那個跟著快的指針一起移動後距離終點n個位置,也就是位在n+1位置,(1跟3距離2而3就是在3的位置)
                                   //這樣慢的下一個就能到達我們要刪去的那個值上
    
    for (int i = 0; i < n; i++) {
        fast = fast->next;
        if (fast == NULL) 
            return head->next;
    }
    
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    
    slow->next = slow->next->next;
    return head;
}