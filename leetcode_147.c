/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;    //NULL head
    }

    struct ListNode *dummy = malloc(sizeof(struct ListNode));    //設置輔助節點並配置動態記憶體
    struct ListNode *sort = head, *cur = head->next;    //設置sort指標指向head, cur指標指向head的下一個
                                                       //想要透過swap的方式來交換值,所以各設置一個指標
    
    dummy->next = head;    //讓輔助節點接上head確保接下來的prev指標能夠在head前面
    dummy->val = 0;
    
    while (cur != 0) {
        if (sort->val <= cur->val) {
            sort = sort->next;
            //透過比較當前的head值跟下一位比較,如果結果是head較小則代表是我們要的升序的狀態
            //而cur就在我們想要他在的位置(大的值)所以要往後歷遍找到需要要插入的資料
            //而指標sort則進入下一筆資料,去做比較,反之如果sort的val大於cur則不是我們要的,就進入else
            //sort在裏頭擔任尾巴的位置因為我們是透過確認兩數大小一前一後,而如果sort=cur則他就在他該在的位置
        } else {
            struct ListNode *prev = dummy;
            while (prev->next->val <= cur->val) {
                prev = prev->next;
            }
            //進入while迴圈前每一次prev指標都會重新指向dummy (head的前頭)在linked list的最前端來從每次從頭歷遍
            //透過每次到head前prev->next每次都是從頭歷遍,直到找到大於cur,則prev就會往後歷遍直到值小於cur,並找到需要插入的資料
            //而prev則會停留在大於cur的值的前一位來確定cur要放入的位置

            sort->next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            //這裡執行分離的動作sort的下一個會跟cur分開連接跟cur的下一個做連接,擔任尾巴的位置也可以說是比較的邊界,而跟下一個要處理的連接繼續當頭
            //讓現在的cur指向prev的下一個(比當前cur大的值)
            //prev在前面找到比cur還大的數,停在前一位,所以下一個就是我們cur要在的位置,也就是下一個我們要做處理的資料
        }
        
        cur = sort->next;
        //把cur初始化讓sort跟cur永遠保持sort在cur的上一個位置而prev則會在else發生回歸到dummy (head前面的位置)
    }
    
    return dummy->next;
    //輔助節點與head連接在head前所以返回他的下一個也就是新的head因為原本的head可能不知道已經被放到哪了
}