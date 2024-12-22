/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 遞迴的方式,去遍歷,由於是前序所以是中,左,右
void func(struct TreeNode* root, int *res, int* returnSize) {
    if(root == NULL) 
        return;      
    // 如果根為null則返回，由於是遞迴的方式,在後面root歷遍的每一個都會在每一次的func中作為root
    // 由於上述原因這裡的root不是單純指一開始的第一個節點,而是指出每一次歷遍到的節點
    // 而root == NULL這個也是作為終止遞迴的條件句
    
    res[(*returnSize)] = root->val;
    // 每一次的func歷遍到的數由於都作為root所以可以用遞迴每一次叫出函式的方式
    // 把每一次的value放入陣列res中,這也是我們要的答案,而在最後返回
    
    (*returnSize)++;
    // returnSize在這裡做為像是index的變數,每一次歷遍到一個新的root
    // 也可以說是叫出了新的func所以又新增一筆資料則放在陣列的下一個
    // 所以做為像是index的returnsize要+1往下一個存放資料
    
    func(root->left, res, returnSize);   // 先左邊在到右側所以先left
    func(root->right, res, returnSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    int* res = malloc(sizeof(int) * 100);  // The return array must be malloced, 所以幫我們要返回的答案分配動態記憶體
    func(root, res, returnSize);
    return res;
}