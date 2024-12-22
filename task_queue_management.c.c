#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 封裝後的任務struct
typedef struct {
   char name[20];
   int execution_time;
   int resources;
} Task;


// 封裝後存放task的queue struct
typedef struct {
   Task *tasks;
   int current_amount;
   int maximum_size;
} PriorityQueue;


// priority queue init
PriorityQueue* create_priority_queue(int maximum_size) {
   PriorityQueue *queue = malloc(sizeof(PriorityQueue));
   queue->tasks = malloc(sizeof(Task) * maximum_size);
   queue->current_amount = 0;
   queue->maximum_size = maximum_size;
   return queue;
}


// print priority queue
void print_priority_queue(PriorityQueue *ptr) {
   printf("Priority Queue: ");
   for (int i = 0; i < ptr->current_amount; i++) {
       printf("[%s] ", ptr->tasks[i].name);
   }
   printf("\n");
}


// swap 函數用於交換兩個Task
void swap_task(Task *a, Task *b) {
   Task temp = *a;
   *a = *b;
   *b = temp;
}


// 計算權重函數，用於比較任務的優先級
int get_task_weight(Task task) {
   // 權重公式，可以根據需要調整
   return task.execution_time * 2 + task.resources; 
}


// 堆化操作，向下調整
void heapify_down(PriorityQueue *ptr, int index) {
   int smallest = index;
   int left = 2 * index + 1;  // 左子節點index
   int right = 2 * index + 2; // 右子節點index


   if (left < ptr->current_amount && get_task_weight(ptr->tasks[left]) < get_task_weight(ptr->tasks[smallest])) {
       smallest = left;
   }


   if (right < ptr->current_amount && get_task_weight(ptr->tasks[right]) < get_task_weight(ptr->tasks[smallest])) {
       smallest = right;
   }


   if (smallest != index) {
       swap_task(&ptr->tasks[index], &ptr->tasks[smallest]);
       heapify_down(ptr, smallest);
   }
}


// 堆化操作，向上調整
void heapify_up(PriorityQueue *ptr, int index) {
   if (index == 0) return;
   int parent = (index - 1) / 2;


   if (get_task_weight(ptr->tasks[index]) < get_task_weight(ptr->tasks[parent])) {
       swap_task(&ptr->tasks[index], &ptr->tasks[parent]);
       heapify_up(ptr, parent);
   }
}


// 插入任務
void insert_task(PriorityQueue *ptr, Task task) {
   if (ptr->current_amount == ptr->maximum_size) {
       printf("Priority Queue is full\n");
       return;
   }
   ptr->tasks[ptr->current_amount] = task;
   ptr->current_amount++;
   heapify_up(ptr, ptr->current_amount - 1);
   printf("插入任務: %s\n", task.name);
   print_priority_queue(ptr);
}


// 移除最高優先級任務
Task remove_highest_priority_task(PriorityQueue *ptr) {
   if (ptr->current_amount == 0) {
       printf("Priority queue is empty\n");
       Task empty_task = {"", -1, -1};
       return empty_task;
   }
   Task highest_priority_task = ptr->tasks[0];
   ptr->tasks[0] = ptr->tasks[ptr->current_amount - 1];
   ptr->current_amount--;
   heapify_down(ptr, 0);
   printf("移除任務: %s\n", highest_priority_task.name);
   print_priority_queue(ptr);
   return highest_priority_task;
}
void function_test();
int main() {
   // function_test();
   // 初始化隊列，最大容量為100
   PriorityQueue *pq = create_priority_queue(100);


   // 插入任務
   Task tasks[] = {
       {"Task A", 10, 3},
       {"Task B", 5, 2},
       {"Task C", 15, 5},
       {"Task D", 8, 4},
       {"Task E", 20, 3},
       {"Task F", 12, 4}
   };


   insert_task(pq, tasks[0]);
   insert_task(pq, tasks[1]);
   insert_task(pq, tasks[2]);
   insert_task(pq, tasks[3]);
   insert_task(pq, tasks[4]);


   // 移除最高優先級任務
   printf("\n移除最高優先級任務\n");
   remove_highest_priority_task(pq);
   printf("\n移除最高優先級任務\n");
   remove_highest_priority_task(pq);
   printf("\n");
   // 插入新的任務
   insert_task(pq, tasks[5]);


   // 釋放內存
   free(pq->tasks);
   free(pq);


   return 0;
}


void function_test() {
   PriorityQueue *pq = create_priority_queue(5);
   Task task1 = {"Task 1", 10, 5};
   Task task2 = {"Task 2", 5, 2};
   Task task3 = {"Task 3", 15, 8};


   insert_task(pq, task1);
   insert_task(pq, task2);
   insert_task(pq, task3);


   // 檢查插入後堆的根是否是最小元素
   if (strcmp(pq->tasks[0].name, "Task 2") != 0) {
       printf("Test Insert Failed: Root is not the smallest element.\n");
   } else {
       printf("Test Insert Passed.\n");
   }
  
   Task removed = remove_highest_priority_task(pq);
   if (strcmp(removed.name, "Task 2") != 0) {
       printf("Test Remove Highest Priority Failed: Wrong task removed.\n");
   } else {
       printf("Test Remove Highest Priority Passed.\n");
   }
   free(pq->tasks);
   free(pq);
}
