/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* buildArray(int *nums, int numsSize, int *returnSize)
{
    int *p=malloc(sizeof(int) * numsSize);  
    //配置動態記憶體, numsSize代表陣列的長度,也代表著要配置幾個記憶體位置,在這邊是6
    for(int i=0; i<numsSize; i++){ 
        p[i] = nums[nums[i]];
        //使用迴圈達成題目要求的給每個位置的陣列新的值
    }
    *returnSize = numsSize; 
    //函式有指標returnSize是希望要給指標指到的值變為numsSize的長度
    return p; 
    //函式為int 不是void 有返回值 且題目敘述return it 而return p是最後返回陣列開始的nums[0]的記憶體位置
}