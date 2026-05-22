顺序栈（用数组存储，简单，访问快，但是容量固定）

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 定义栈结构
typedef struct {
    int data[MAXSIZE];
    int top;  // 栈顶指针
} Stack;

// 初始化
void InitStack(Stack *s) {
    s->top = -1;
}

// 判空
int IsEmpty(Stack *s) {
    return s->top == -1;
}

// 判满
int IsFull(Stack *s) {
    return s->top == MAXSIZE - 1;
}

// 入栈
void Push(Stack *s, int x) {
    if (IsFull(s)) {
        printf("栈满！\n");
        return;
    }
    s->data[++s->top] = x;
}

// 出栈
int Pop(Stack *s) {
    if (IsEmpty(s)) {
        printf("栈空！\n");
        return -1;
    }
    return s->data[s->top--];
    }
    
    // 取栈顶元素
    int GetTop(Stack *s) {
        if (IsEmpty(s)) {
            printf("栈空！\n");
           return -1;
        }
        return s->data[s->top];
    }
    
    // 测试
    int main() {
        Stack s;
          InitStack(&s);
        
        Push(&s, 10);
        Push(&s, 20);
        Push(&s, 30);
        
        printf("栈顶元素: %d\n", GetTop(&s));
        
        printf("出栈: %d\n", Pop(&s));
        printf("出栈: %d\n", Pop(&s));
        
        return 0;
    }
    
    链式栈（不需要固定大小，用链表实现，不会溢出，但是需要额外指针空间）
    
    #include <stdio.h>
    #include <stdlib.h>
    
    // 定义节点
    typedef struct Node {
        int data;
        struct Node *next;
    } Node;
    
    // 定义栈
    typedef struct {
        Node *top;
    } Stack;
    
    // 初始化
    void InitStack(Stack *s) {
        s->top = NULL;
    }
    
    // 判空
    int IsEmpty(Stack *s) {
        return s->top == NULL;
    }
    
    // 入栈
    void Push(Stack *s, int x) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = x;
        newNode->next = s->top;
        s->top = newNode;
    }
    
    // 出栈
    int Pop(Stack *s) {
        if (IsEmpty(s)) {
            printf("栈空！\n");
            return -1;
        }
        Node *temp = s->top;
        int val = temp->data;
        s->top = temp->next;
        free(temp);
        return val;
    }
    
    // 取栈顶
    int GetTop(Stack *s) {
        if (IsEmpty(s)) {
            printf("栈空！\n");
            return -1;
        }
        return s->top->data;
    }
    
    // 测试
    int main() {
        Stack s;
        InitStack(&s);
        
        Push(&s, 100);
        Push(&s, 200);
        Push(&s, 300);
        
        printf("栈顶元素: %d\n", GetTop(&s));
        
        printf("出栈: %d\n", Pop(&s));
        printf("出栈: %d\n", Pop(&s));
        
        return 0;
    }    
    
    
