cCopy/**
* Definition for a binary tree node.
* struct TreeNode {
* int val;
* struct TreeNode *left;
* struct TreeNode *right;
* };
*/
typedef struct TreeNode TreeNode;
//使用 c 語言函式庫 qsort 裡呼叫 cmp 函數去比較兩數的大小,qsort 函數會在幫我們把每
一列的數字和去做排序
long long cmp(const void* a, const void* b) {
    long long sub = *(long long *)a - *(long long *)b;
    return sub < 0 ? -1 : 1;
    //相減過後的結果如果小於 0 則是後者大,則返回-1 反之前者大於則返回 1
}
long long kthLargestLevelSum(struct TreeNode* root, int k) {
    TreeNode* que[100001] = { NULL }; //依據題目要求 10^5,所以要把 array 設
    定成這個大小
    long long ans[100001] = { 0 };
    //head 跟 tail 是作為 queue 的索引作為放入放入 queue 的索引,cnt 是用來數當前
    的層數如果處理完第一層則往下一層時 cnt 增加 1,size 則是作為當前層數有多少節點,作為
    while 裡的參數來決定要做幾次 while 迴圈
    int head = 0, tail = -1, cnt = 0, size = 0;
    if(root != NULL) que[++tail] = root;
    //root 不為 NULL 放入第一個在 queue 裡第 0 位為 root
    while(head <= tail) {
        size = tail - head + 1;
        //透過 head 跟 tail 的索引來尋找當前總共有多少節點,由於 tail 跟 head 不會
        重置則每次在迴圈新增 array 裡的資料時 tail 會一起增加透過這樣的方式可以計算出當前層
        數有多少節點
        while(size-- > 0) {
            TreeNode* cur = que[head++];
            //把 while 迴圈裡的當前已被放入資料給 cur 指針
            ans[cnt] += cur->val;
            //當前層數存放答案,透過每一次 while 放入前一次處理的數並累加,直到離
            開 while 並 cnt++後到下一層
            if(cur->left) que[++tail] = cur->left;
            //遍歷左子樹不迴 NULL 時則放入 queue 中,
            if(cur->right) que[++tail] = cur->right;
        }
        cnt++;
    }
    if(k > cnt) return -1;
    //依照題目 k 大於 cnt(層數時)返回-1
    qsort(ans, cnt, sizeof(long long), cmp);
    //透過 qsort 函式排序答案的大小
    return ans[cnt - k];
    //cnt 代表最大的層數如果-k 代表要得最大的層數合的答案
}