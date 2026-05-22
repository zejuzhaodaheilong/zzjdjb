#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

// 初始化
void InitQueue(SqQueue *q) {
    q->front = q->rear = 0;
}

// 判空
int IsEmpty(SqQueue *q) {
    return q->front == q->rear;
}

// 判满（循环队列关键）
int IsFull(SqQueue *q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

// 入队
int EnQueue(SqQueue *q, int x) {
    if (IsFull(q)) {
        printf("队列已满！\n");
        return 0;
    }
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAXSIZE;
    return 1;
}

// 出队
int DeQueue(SqQueue *q, int *x) {
    if (IsEmpty(q)) {
        printf("队列为空！\n");
        return 0;
    }
    *x = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 1;
}

// 测试
int main() {
    SqQueue q;
    InitQueue(&q);
    
    EnQueue(&q, 10);
    EnQueue(&q, 20);
    EnQueue(&q, 30);
    
    int x;
    while (!IsEmpty(&q)) {
        DeQueue(&q, &x);
        printf("%d ", x);
    }
    
    return 0;
}
