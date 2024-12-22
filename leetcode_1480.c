int* runningSum(int* nums, int numsSize, int* returnSize) {
    int* result = malloc(numsSize * sizeof(int));
    //配置動態記憶體給新的陣列存放相加過後的最終結果
    
    int temp = 0;
    //初始化變數temp 來存放迴圈中每跑一次加上下一個, 並放置在相對應的新陣列位子中
    
    *returnSize = numsSize;
    
    for(int i = 0; i < numsSize; i++) {
        temp += nums[i];
        result[i] = temp;
    }
    
    return result;
}