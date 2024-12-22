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

// BTS 二叉樹的值有大小分布的規則,所以我們可以透過前一個數字跟後一個數字的對比來知道我們有沒有遇到新的數字
// 舉例來說1的左子樹是不會大於1而右子樹則可以
// 所以可以透過是否遇到重複的數的方式來找到眾數,在條件設計中如果遇到PRE跟CUR不一樣的數則讓COUNT回到1
// 之所以是1是當出現新的數字本身就能作為1
int* findMode(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL)
        return NULL;
        
    int* res = malloc(sizeof(int) * 10000);
    // res為最後答案的陣列,題目要求The returned array must be malloced,所以我們分配動態記憶體
    
    int count = 0;
    int maxCount = 0;
    // pre用於指向cur的前一個節點來去跟cur做比較去知道有沒有新的數字進行變化
    // 如果有則count變回1,所以pre一開始指向null
    struct TreeNode* pre = NULL;
    struct TreeNode* cur = root;
    struct TreeNode* stack[10000];    // 題目要求range 10^4所以給予10000
    int top = -1;                     // 作為stack的index
    
    while (cur != NULL || top != -1) {
        if (cur != NULL) {
            stack[++top] = cur;
            cur = cur->left;
            // 開始遍歷陣列,並且把在左子樹歷遍到的節點給放入stack之中,top就做為array中的index
        } else {
            cur = stack[top--];       // 遇到NULL的情況,cur被stack存放的資料回到上一筆資料
            
            if (pre == NULL)          // pre是null的情況代表歷遍剛開始遇到第一個數,要幫count先賦值為1
                count = 1;
            else if (pre->val == cur->val)  // 要是前值還是等於現在的值代表值是一樣的則COUNT+1
                count++;
            else                            // 代表遇到不同的數值了所以count回到1
                count = 1;
                
            pre = cur;
            
            if (count == maxCount) {        
                // 透過每一個數的count去給maxcount賦值,若最後count的值是等於maxcount
                // 代表當下的VAL就是我們在找的眾數
                res[(*returnSize)++] = cur->val;
            }
            
            if (count > maxCount) {
                // 如果新出現的數的count更多多過maxcount則覆蓋maxcount原本的值
                // 把當前count的值當成maxcount透過這樣的方式找到maxcount
                // 並且更新res陣列裡的答案
                maxCount = count;
                *returnSize = 0;
                res[(*returnSize)++] = cur->val;
            }
            
            cur = cur->right;         // 開始歷遍右子樹
        }
    }
    
    return res;
}