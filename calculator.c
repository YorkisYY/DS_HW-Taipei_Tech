#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000000

struct Stack {
    char items[MAX_SIZE];
    int top;
};

void initialize(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack *s, char value) {
    if (isFull(s)) {
        printf("Error: Stack is full\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

char pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

char peek(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

int getPrecedence(char op) {
    switch (op) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

double doCalulate(char op, double left, double right) {
    switch (op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        case '%':
            return fmod(left, right);
        case '^':
            return pow(left, right);
        default:
            return 0;
    }
}

double evaluateExpression(char *expr) {
    struct Stack operators;                   // 使用一個stack儲存operator
    initialize(&operators);                   // 使用init function 設定top = -1 代表為空stack
    double *numStack = malloc(MAX_SIZE + 1);  // 使用一個array儲存operands, 使用的方式類似Stack的LIFO
    int numTop = -1;                         // 使用一個integer讓我們可以找到最後進入numStack的element
    
    // (1+2)*3
    while (*expr) {              // 當expr不為空時 開始執行將operator和operands放入stack&array的操作
        char currChar = expr[0];  // 當前第一個char

        if (isdigit(currChar)) {  // 如果是數字的話將數字放進numStack
            double num = strtod(expr, &expr);
            numStack[++numTop] = num;
        } else if (currChar == '(') {  // 如果是 '(' 將他放進operators stack
            push(&operators, *expr);
            expr++;                    // 將expr向前推進
        } else if (currChar == ')') {  // 如果是')' 我們將開始持續pop operators stack並與兩個數字進行運算後放回numStack 直到下一個operators中的element為'('
            while (!isEmpty(&operators) && peek(&operators) != '(') {
                double r = numStack[numTop--];
                double l = numStack[numTop--];
                char op = pop(&operators);
                numStack[++numTop] = doCalulate(op, l, r);  // 將結果放回numStack
            }
            pop(&operators);  // 運算完畢將 '(' 從stack中移除
            expr++;          // 將expr向前推進
        } else {
            while (!isEmpty(&operators) && getPrecedence(peek(&operators)) >= getPrecedence(*expr)) {
                // 如果非數字或是()：
                // peek stack top 的operator是否優先度高於將目前的operator
                // 如果高於則先使用stack top 的 operator計算並將結果儲存回numStack， 再將目前的operator放入stack
                // 不高於則直接將目前的operator放入stack
                double r = numStack[numTop--];
                double l = numStack[numTop--];
                char op = pop(&operators);
                numStack[++numTop] = doCalulate(op, l, r);  // 將結果放回numStack
            }
            push(&operators, *expr);
            expr++;  // 將expr向前推進
        }
    }

    while (!isEmpty(&operators)) {  // 經過上面過程 最後完成簡單算式的計算直到operator為空
        double r = numStack[numTop--];
        double l = numStack[numTop--];
        char op = pop(&operators);
        numStack[++numTop] = doCalulate(op, l, r);
    }

    return numStack[numTop];
}

void runTest();

int main() {
    // 運行測試
    // runTest();
    char *input = malloc(MAX_SIZE + 1);  // 在heap分配記憶體

    printf("Enter expression: ");

    if (!input) {
        fprintf(stderr, "malloc failed.\n");
        return 1;
    }

    if (fgets(input, MAX_SIZE + 1, stdin)) {
        input[strcspn(input, "\n")] = 0;
    }
    
    double output;
    output = evaluateExpression(input);
    printf("Output: %.12lf\n", output);

    free(input);
    return 0;
}

// 運行測試
void runTest() {
    char case_1[MAX_SIZE] = {'1', '+', '3', '-', '2'};
    printf("Expression: 1+3-2\n");
    double output_1 = evaluateExpression(case_1);
    printf("Output: %.12lf\n\n", output_1);

    char case_2[MAX_SIZE] = {'1', '+', '2', '*', '3'};
    printf("Expression: 1+2*3\n");
    double output_2 = evaluateExpression(case_2);
    printf("Output: %.12lf\n\n", output_2);

    char case_3[MAX_SIZE] = {'1', '-', '2', '*', '3'};
    printf("Expression: 1-2*3\n");
    double output_3 = evaluateExpression(case_3);
    printf("Output: %.12lf\n\n", output_3);

    char case_4[MAX_SIZE] = {'(', '1', '+', '2', ')', '*', '3'};
    printf("Expression: (1+2)*3\n");
    double output_4 = evaluateExpression(case_4);
    printf("Output: %.12lf\n\n", output_4);

    char case_5[MAX_SIZE] = {'2', '^', '3', '+', '2', '*', '5'};
    printf("Expression: 2^3+2*5\n");
    double output_5 = evaluateExpression(case_5);
    printf("Output: %.12lf\n\n", output_5);

    char case_6[MAX_SIZE] = {'2', '^', '3', '^', '4', '+', '1'};
    printf("Expression: 2^3^4+1\n");
    double output_6 = evaluateExpression(case_6);
    printf("Output: %.12lf\n\n", output_6);
}