/**
* Definition for a binary tree node.
* struct TreeNode {
* int val;
* struct TreeNode *left;
* struct TreeNode *right;
* };
*/
//透過遞迴函式 search 在 tree 中尋找插入並插入值 val
void search(struct TreeNode* root, int val)
{
   if(val < root->val )
   {
       if(root->left != NULL)
           search(root->left,val);
       //使用遞迴的方式讓每一次的遍歷到的節點跟 val 比值的大小,若較小則繼續歷遍左樹反之則是歷遍右樹直到遇到空值為止
       else
       {
           root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
           root->left->val = val;
           root->left->left = NULL;
           root->left->right= NULL;
       //若 val <root, 由於 BST 的特性, 小於 root 的 val 會在左樹或是接下來左側的節點,若 val < root, 則應該去遍歷左樹或左節點
       //但若左樹為空或是透過遞迴的情況遇到空值時就是插入的時機,則插入 val 變成 root 的 child,並且讓新的 val 的左右 child 的值接上 NULL
       }
   }
   else
   {
       if(root->right != NULL)
           search(root->right,val);
       //透過呼叫 search 函式的方式每一次都讓 root->left/right 當 root 去跟 val 比較,進而去決定去遍歷左節點又或是右節點
       else
       {
           root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
           root->right->val = val;
           root->right->left = NULL;
           root->right->right= NULL;
       //同理在每一次 root/root->left/right 時決定插入的時機,一次次遍歷直到遇到空值則插入在遍歷到當前空值處
       }
   }
}


struct TreeNode* insertIntoBST(struct TreeNode* root, int val)
{
   if(root == NULL)
   {
       struct TreeNode* newHead = (struct TreeNode*)malloc(sizeof(struct TreeNode));
       newHead->val = val;
       newHead->left = NULL;
       newHead->right= NULL;
       return newHead;
       //假設 root 為空則直接插入 val 成為 root 並讓左右節點(child)為 NULL
   }
   search(root,val);
   return root;
}