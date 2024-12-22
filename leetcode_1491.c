double average(int* salary, int salarySize) {
    double min = salary[0], max = 0, sum = 0, result = 0;
    // 最後return的資料是double，所以在這裡給所有變數設定為double的資料型態
    
    for (int i = 0; i < salarySize; i++) {
        if (salary[i] > max) {
            max = salary[i];
        }
        // 迴圈內透過設定max變數為0去做比較,要是新的數字大於原本的即取代原本的資料
        // 最終透過跑完一圈迴圈來比較過每一組數值
        
        if (salary[i] < min) {
            min = salary[i];
        }
        // 尋找min不能跟找max一樣,如果初始值設為0然後每一組去比較的話,最後min還是為0
        // 所以一開始把min初始化為salary[0],去跑一遍做比較
        
        sum += salary[i];
        // sum初始值為0,跟salary陣列中的每一筆資料相加即可得到總值
    }
    
    result = sum - max - min;
    // 由於得到所有需要的資料,跳脫出迴圈,去除掉最大最小的總值 = 總值 - 最小 + 最大
    
    return result / (salarySize - 2);
    // salarysize表陣列中有幾筆資料,要算平均值前則需要知道總數
    // 而總數得先扣除已經在總值減少的2筆資料,分別為最小最大
}