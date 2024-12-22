/**
* Definition for a binary tree node.
* struct TreeNode {
* int val;
* struct TreeNode *left;
* struct TreeNode *right;
* };
*/
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
   if (!root) return NULL;
   //root 檢查根結點 root 是否為 0,若為 0 則返回 NULL
   if (key < root->val) root->left = deleteNode(root->left, key);
   //利用 BST 的特性左值小於 root 右值則大於,來區分 key 接下來要遍歷的是左樹或是左節點
   //透過遞迴的方式再次呼叫 deleteNode 函式,並且每一次都是讓 root->left or right 去當 root 跟 key 去做比較來決定要往當前的左節點或是右節點
   if (key > root->val) root->right = deleteNode(root->right, key);
   //在每一次歷遍之中 root->left/right 最後找到相等的值而這就是我們要刪除的,但有幾個情況要分別處理
   if (key == root->val) {
       if (root->left == NULL) return root->right;
       //當前要刪除的點,沒有左節點,透過 return root->right 的方式去刪除,返回當前節點的右子樹
       if (root->right == NULL) return root->left;
       //同樣沒有右節點時,透過返回左節點的方式刪除
       struct TreeNode* mostRight = root->left;
       while (mostRight->right)
           //當左右都有節點時,在左子數尋找右節點最大的值去取代當前的 root
           mostRight = mostRight->right; //這裡的 mostright 就是最大值
       mostRight->right = root->right; //將 mostright 的右子樹設置為root 的右子樹
       //則 mostright 繼承了當前節點 root 的右子樹,並成為新的右子樹根節點。

       return root->left; //返回當前節點 root 的左子樹
   }

   return root;
}