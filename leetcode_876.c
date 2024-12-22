/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/

struct ListNode* middleNode(struct ListNode* head) {
   struct ListNode *q1 = head;    //初始化指標指向head
   int size = 0;                  //找數列的大小
   
   while (q1 != NULL) {          //值不是空的就增加size
       size++;
       q1 = q1->next;            //指針再其中歷遍,最後遇到空值離開while迴圈
   }
   
   int j = size/2;               //size除以2後找到我們要消除的數量, example 1 = 2 example 2 = 3
   q1 = head;
   for (int i = 0; i < j; i++) {
       q1 = q1->next;            //移動q1到我們要當作輸出答案的head的位置
   }
   return q1;                    //返回q1
}

//solution 2:
/*
struct ListNode* middleNode(struct ListNode* head) {
   struct ListNode* fast = head;    //設置快慢指標
   struct ListNode* slow = head;
   
   while (fast != NULL && fast->next != NULL) {
       slow = slow->next;           //慢的指標一次只跑一個而塊的一次跑兩個最後的慢的會到我們要的new head
       fast = fast->next->next;
   }
   return slow;                     //返回慢的做為答案
}
*/