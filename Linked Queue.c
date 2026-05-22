#include <stdio.h>
#include <stdlib.h>

// 结点结构
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

// 队列结构
typedef struct {
    QNode *front;
    QNode *rear;
} LinkQueue;

// 初始化
void InitQueue(LinkQueue *q) {
    q->front = q->rear = (QNode *)malloc(sizeof(QNode));
    q->front->next = NULL;
}

// 判空
int IsEmpty(LinkQueue *q) {
    return q->front == q->rear;
}

// 入队
void EnQueue(LinkQueue *q, int x) {
    QNode *s = (QNode *)malloc(sizeof(QNode));
    s->data = x;
    s->next = NULL;
    
    q->rear->next = s;
    q->rear = s;
}

// 出队
int DeQueue(LinkQueue *q, int *x) {
    if (IsEmpty(q)) {
        printf("队列为空！\n");
        return 0;
    }
    
    QNode *p = q->front->next;
    *x = p->data;
    
    q->front->next = p->next;
    
    // 如果删除的是最后一个结点
    if (q->rear == p) {
        q->rear = q->front;
    }
    
    free(p);
    return 1;
}

// 测试
int main() {
    LinkQueue q;
    InitQueue(&q);
    
    EnQueue(&q, 100);
    EnQueue(&q, 200);
    EnQueue(&q, 300);
    
    int x;
    while (!IsEmpty(&q)) {
        DeQueue(&q, &x);
        printf("%d ", x);
    }
    
    return 0;
}
