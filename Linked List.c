#include <stdio.h>
#include <stdlib.h>

#define ok 1 
#define error 0

// 定义结点
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 初始化链表（带头结点）
Node* InitList() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 插入：在第 i 个位置插入元素 e
int ListInsert(Node *head, int i, int e) {
    Node *p = head;  // p 用来移动定位
    int j = 0;
    
    // 找到第 i-1 个结点
    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    
    if (p == NULL) return 0;
    
    // 创建新结点
    Node *s = (Node*)malloc(sizeof(Node));
    s->data = e;
    
    // 关键两步（不能交换顺序！）
    s->next = p->next;
    p->next = s;
    
    return ok;
}

// 删除：删除第 i 个结点
int ListDelete(Node *head, int i, int *e) {
    Node *p = head;
    int j = 0;
    
    // 找到第 i-1 个结点
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    
    if (p->next == NULL) return 0;
    
    Node *q = p->next;
    *e = q->data;
    
    // 删除操作（只需改一个指针）
    p->next = q->next;
    free(q);
    
    return 1;
}

// 按值查找
Node* LocateElem(Node *head, int e) {
    Node *p = head->next;
    
    while (p != NULL) {
        if (p->data == e)
        return p;
        p = p->next;
    }
    
    return NULL;
}

// 遍历输出
void PrintList(Node *head) {
    Node *p = head->next;
    
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 主函数测试
int main() {
    Node *L = InitList();
    
    // 插入数据
    ListInsert(L, 1, 10);
    ListInsert(L, 2, 20);
    ListInsert(L, 3, 30);
    
    printf("链表元素：");
    PrintList(L);
    
    // 删除
    int x;
    ListDelete(L, 2, &x);
    printf("删除的元素：%d\n", x);
    
    printf("删除后链表：");
    PrintList(L);
    
    // 查找
    Node *res = LocateElem(L, 30);
    if (res != NULL)
    printf("找到元素：%d\n", res->data);
else
    printf("未找到\n");
    
    return 0;
}
