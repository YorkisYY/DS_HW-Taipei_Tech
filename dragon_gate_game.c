#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 建立名為 Cards 的 Struct*/
//宣告一個struct結構體,叫做cards裡面有我們要的花色以及數字其中資料型態分別為字元以及整數
typedef struct {
    char suits;
    int number;
} Cards;

//額外定義一個函式來讓數字相同時可以透過比較花色來決定最終的大小，透過給予的參數來回傳數字去做比大小
int suitWeight(char suits) {
    switch(suits) {
        case 'S': return 4;
        case 'H': return 3;
        case 'D': return 2;
        case 'C': return 1;
        default: return 0;
    }
}

int shoot(Cards* c1, Cards* c2, Cards* c3) {
    // Hint! 印出花色數字、花色數字、花色數字
    printf("\t%c%d\t%c%d\t%c%d\n ", c1->suits, c1->number, c2->suits, c2->number, c3->suits, c3->number);
    //透過main裡面的函式，來讓給予的參數能跑進shoot函式，但由於近來的是指標得透過->這樣的方式來訪問又或是(*c1).suits
    
    int min, max;
    char tempmin, tempmax;
    
    if(c1->number > c2->number) {
        min = c2->number;
        max = c1->number;
        tempmin = suitWeight(c2->suits);
        tempmax = suitWeight(c1->suits);
    } else {
        min = c1->number;
        max = c2->number;
        tempmin = suitWeight(c1->suits);
        tempmax = suitWeight(c2->suits);
    }
    //首先把隨機到的前兩張卡牌(C1,C2)並分出小跟大，這樣才能決定可以獲勝的範圍，也以便於接下來的操作,並且儲存大的花色以及小的來應對要是數字一樣的情況

    if (c3->number > min && c3->number < max) {
        printf("\t獲勝\n");
    } else if (c3->number == min && suitWeight(c3->suits) > tempmin) {
        // c3 的數值等於min的情況，並且花色大於 min 的花色
        printf("\t獲勝\n");
    } else if (c3->number == max && suitWeight(c3->suits) < tempmax) {
        // c3 的數值等於 max的情況，並且花色小於 max 的花色
        printf("\t獲勝\n");
    } else {
        printf("\t失敗\n");
        //都沒符合就失敗
    }
    return 0;
}

int main() {
    Cards cards[52];                    //宣告有52張撲克牌的陣列
    char suits[] = {'S','H','D','C'};   // 4種花色
    
    //1. 建立牌堆-----------------------------------------------------------------------------
    printf("第一題：產生牌堆\n");
    Cards *ptr_cards = cards;   //初始化指標，宣告指標指向結構體Cards 並且指向其中的cards
    char *ptr_suits = suits;    //初始化指標，是字元指標，指向suits陣列
    
    for (int suit = 0; suit < 4; suit++) {
        for (int num = 1; num <= 13; num++) {   //一組花色有13張牌,透過巢狀迴圈先產生把同一種花色的一到13張生產完再到下一個花色
            (*ptr_cards).suits = *ptr_suits;
            ptr_cards->number = num;
            ptr_cards++;
        }
        ptr_suits++;
    }
    
    ptr_cards = cards;
    for (int i = 0; i < 52; i++) {      //把給予的卡牌輸出出來，並且再輸出１３張後換行
        printf(" %c%d", ptr_cards[i].suits, ptr_cards[i].number);
        if ((i + 1) % 13 == 0)
            printf("\n");
    }
    
    // 2. 射龍門------------------------------------------------------------------------------
    srand(time(NULL));    // 系統預設的隨機函數是1 並不隨機，透過這個函式可以改善這問題
    printf("\n\n第二題:射龍門\n");
    printf("\t第一張\t第二張\t第三張\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%d.", i + 1);    //透過隨機生成的數字除以52的餘數來隨機產出陣列中的卡牌
        int c1 = rand() % 52;
        int c2 = rand() % 52;
        
        while (c2 == c1) {
            c2 = rand() % 52;    //要是c1 = c2 的話就要重新產生，一副撲克牌沒有重複的牌
        }
        
        int c3 = rand() % 52;
        while (c3 == c1 || c3 == c2) {
            c3 = rand() % 52;    //同理要是c3跟c1和c2重複也得，重新產出
        }
        
        shoot(&cards[c1], &cards[c2], &cards[c3]);
    }
    
    printf("\n\n");
    return 0;
}