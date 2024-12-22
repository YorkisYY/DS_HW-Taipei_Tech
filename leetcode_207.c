bool canFinish(int numCourses, int** prerequisites, int
prerequisitesSize, int* prerequisitesColSize){
    if(prerequisitesSize == 0) //如何任何課有先修要求則先修的 Size 不會為 0,
如果為 0 則代表能上完,所以可以直接返回 True
    {//雙指針是因為要表示二維陣列
        return true;
    }
    int * ans = malloc(sizeof(int) * numCourses); //用 ans 陣列存放每個課
程的入度,有多少課程需要先修這個課程
    int i = 0;
    for(i = 0; i < numCourses; i++) //初始化被分配動態記憶體的 ans 陣列每一
格為 0,確保課程的入度計算前為 0,不然其中的值可能為隨機
    {
        ans[i] = 0;
    }
    int j = 0 , res = 0;
    for(i = 0; i < prerequisitesSize; i++)//更新每个点的入度,由於
prerequisites 是一個長度為二的陣列每個元素包含兩個整數,
    {//透過 ans 裡面[]的方式去歷遍 prerequisites 陣列裡面第一個的元素,第一個代表
需要某先修課,所以第一個的元素是需要先修課的
    //透過取出第一個元素,來知道什麼元素有先修課讓他的入度增加並統計在 ans 陣列中
    //舉例來說 [1,0] /n [2,0] 1 跟 2 都需要 0 當先修課,於是把其中的第[0][0]跟
[1][0]取出我們就知道我們要增加入度的課程元素是誰了
    //以此例來說是 1 跟 2 元素,然後在 i 遍歷完後就會去變成 ans[1]++, 讓 ans 鎮
列中的第 1 個元素+1 達成入度+1 的存儲
        ans[prerequisites[i][0]]++;
    }
    for(i = 0; i < numCourses; i++)
    {
        if(ans[i] == 0)//歷遍我們的 ans 陣列要是 ans 裡面的第 i 格為 0 代表不需要
先修所以可以幫 res 這個數增加
        //直到其=numCourses 我們要上的課的總數代表我們可以學完,那就可以
returntrue
        //透過當前已被完成的第 i 個課程,來去歷遍跟 i 有入度(先修關係的元素)
        {
            res++;//學習完一個則++
            if(res == numCourses)
            {
                return true;
            }
            for(j = 0; j < prerequisitesSize; j++)//透過 int j 歷遍有
prerequisitesSize 裡需要先修的項目
            //如果被遍歷到的 i 值跟其中 prerequisitesSize 陣列裡的元素相符的話,
就把這個在 ans 裡被增加的入度減少掉
            //來達到假設當前沒有需要先修入度為 0 的課程完成,那其餘依賴當前 i 元素
的課程則可以-1 入度
            //透過減少 ans 陣列中存放的入度如果被--變成 0 代表有入度的課程是能被
完成的
            {
                if(prerequisites[j][1] == i)
                {
                    ans[prerequisites[j][0]]--;
                }
            }
            ans[i]--;//防止陷入 i == 0 的 if 無限迴圈循環,所以把已經被處理過的
元素變成-1
            i = -1;
        }
    }
    return false; //條件不滿足代表其中有元素不為-1,理論上說如果有辦法上完所有課
最後的每一個值在 ans 陣列裡都為-1
}