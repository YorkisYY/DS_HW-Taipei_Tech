#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 6 //Define the maximum stack capacity
#define MAXQUEUE 6 //Define the maximum queue capacity

//Implement Stack using Array
int stack[MAXSTACK]; 
int top=-1; //stack top index

//Determine whether stack is empty
int stackisEmpty(){
    if(top ==-1)
        return 1;
    else 
        return 0;
    /*Please fill in the code here*/
}

//Push data into stack
void push(int data){
    if(top >= MAXSTACK -1 )
        printf("stack滿了\n");
    else{
        stack[++top] = data; //跟top++ 差異為,++top會先將top值加1再返回, 而top++會先返回top當前值然後再加1
        //在這裡要先加1再放入stack中,反之如果使用top++會把未加的放入stack中
    }
    /*Please fill in the code here*/
}

//pop stack data
int pop(){
    int data;
    if(stackisEmpty() == 1)
        printf("stack為空\n"); //確認stack是否是空的,透過函式返回值是否為1(真)來確認
    else{
        data = stack[top--]; //有資料可以移除時就透過top--移除頂部的數據
        return data;
    }
    return 0; //表示false 回傳0
    /*Please fill in the code here*/
}

//Get stack top information
int getTop(){
    return stack[top];
    /*Please fill in the code here*/
}
//////////////////////////////////////////////////
//Implement Queue using Array
int queue[MAXQUEUE]; 
int First=-1; //The front of queue
int Last=-1; //The end of the queue 
int Size=0; //queue size

//Determine whether queue is empty
int queueisEmpty()
{   if (First == -1 && Last == -1 )
        return 1;
    else{
        return 0;
    }
    /*Please fill in the code here*/
}

//Put data into the queue (put it from the end)
void Enqueue(int a){
    if(Size == MAXQUEUE) {
        printf("queue滿了\n");
    } else {
        if (First == -1) First = 0; 
        Last = (Last + 1) % MAXQUEUE; 
        queue[Last] = a; //透過+1的方式讓last+1成為對的索引
        Size++;//因為加入新值所以增加大小
    }
}
    /*Please fill in the code here*/


//Take out the data in the queue (get it from the front end)
int Dequeue(){
    int data;
    if(queueisEmpty() == 1){
        printf("queue為空\n");
        return 0;//表示False, 表示無法移除
    }else {
        data = queue[First];
        First = (First +1)%MAXQUEUE; 
        Size --; //因為減少了所以減少大小
        return data;
        }
    return 0; //False,說明quenen為空,回傳0; 
    }
    
    /*Please fill in the code here*/
    /*Hint:After taking it out, the value of the array must be moved forward.*/


//Get the front-end value
int getFirst()
{   return queue[First];
    /*Please fill in the code here*/
}

//Get the value at the end
int getLast()
{   return queue[Last];
    /*Please fill in the code here*/
}

//Get queue size
int getSize()
{   return Size;
    /*Please fill in the code here*/
}

int main() {
    int student_preference[MAXQUEUE] = {1, 1, 1, 0, 0, 1};
    for (int i = 0; i < MAXQUEUE; i++) {
        Enqueue(student_preference[i]);
    }

    int sandwiches_type[MAXSTACK] = {1, 0, 0, 0, 1, 1};
    for (int i = 0; i < MAXSTACK; i++) {
        push(sandwiches_type[MAXSTACK-i-1]);
        //大小設定為6但是由0為起始點但只有6筆資料要以0~5的索引放入資料所以-1,而-i是透過這樣的方式讓資料以倒序的方式放入stack滿足stack 的 last in first out
    }

    int not_Match_Round = 0;
    // 設置這個沒有配對到的整數,來確保最後能夠停止while迴圈,且三明治去跟剩下的學生都比較過,而人數(size)就代表剩下的三明治要比較幾次
    //設置這個的話while迴圈才能結束

    while (top >= 0 && Size > 0) {
    // 確定裡面不是空的,就能一直去跑做比較
    if (getTop() == getFirst()) { //去做比較要是stack的top跟queue的first一樣則用dequeue跟pop函式消除各自的資料
        Dequeue(); 
        pop(); 
        not_Match_Round = 0; // 要是有一樣的就要重置,去確保最後一次讓三明治跟所有學生可以都比較到,如果沒有函式會提早結束產生錯誤結果
    } else {
        Enqueue(Dequeue());
        not_Match_Round++;
        }
        //如果沒有一樣,則會讓Dequeue函式的返回值(data)就是queue裡的first去重新enqueue加入queue中
        if (not_Match_Round >= Size) {
            break; // not_match_found 函式跟剩下queue的size一樣的話代表已經把當前的三明治跟所有學生比較過一次了,所以可以break結束並且size代表還有多少人數而那個人數就是要找的有多少學生沒吃到三明治
        }
    
}
    printf("有 %d 位學生沒有吃到三明治\n", Size);
    return 0;
}