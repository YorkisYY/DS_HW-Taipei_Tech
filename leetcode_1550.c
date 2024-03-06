bool threeConsecutiveOdds(int* arr, int arrSize) {
    // 檢查是否有充足的數量,題目要求三個連續奇數,若沒有返回false
    if(arrSize < 3){
        return false;
    }
    // arrsize -3 是確保不會超過陣列的總數量,因為是以三個一組,做的最後一次應該是倒數第三個為最後一次
    for(int i=0; i <= arrSize - 3; i++){
       //分別確定三者是否為奇數,and來表示三個都得是值數那結果才會return true
       if ((arr[i] % 2 == 1) && (arr[i+1] % 2 == 1) && (arr[i+2] % 2 == 1)){
           return true;
       }
    }
    return false;
    /*
    脫離迴圈如果都沒有滿足條件的情況下直接返回false,不在迴圈寫else就是怕只能做一次迴圈就結束了,
    畢竟只有奇數或偶數,所以放在迴圈外
    */
}