#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  // 顺序表最大容量

// 定义顺序表
typedef struct {
    int data[MAXSIZE];
    int length;  // 当前元素个数
} SeqList;

// 初始化顺序表
void initList(SeqList *L) {
    L->length = 0;
}

// 插入元素（在第pos位置插入）
int insert(SeqList *L, int pos, int value) {
    if (pos < 1 || pos > L->length + 1) {
        printf("插入位置非法\n");
        return 0;
    }
    if (L->length >= MAXSIZE) {
        printf("顺序表已满\n");
        return 0;
    }
    
    // 元素后移
    for (int i = L->length; i >= pos; i--) {
    L->data[i] = L->data[i - 1];
}

L->data[pos - 1] = value;
L->length++;

return 1;
}

// 删除元素
int delete(SeqList *L, int pos) {
if (pos < 1 || pos > L->length) {
    printf("删除位置非法\n");
    return 0;
}

// 元素前移
for (int i = pos; i < L->length; i++) {
    L->data[i - 1] = L->data[i];
}

L->length--;
return 1;
}

// 查找元素（返回位置，从1开始）
int search(SeqList *L, int value) {
for (int i = 0; i < L->length; i++) {
    if (L->data[i] == value) {
        return i + 1;
    }
}
return -1;
}

// 打印顺序表
void printList(SeqList *L) {
for (int i = 0; i < L->length; i++) {
    printf("%d ", L->data[i]);
}
printf("\n");
}

// 主函数测试
int main() {
SeqList L;
initList(&L);

// 插入元素
insert(&L, 1, 10);
insert(&L, 2, 20);
insert(&L, 3, 30);
insert(&L, 2, 15);

printf("顺序表内容: ");
printList(&L);

// 删除元素
delete(&L, 3);
printf("删除后: ");
printList(&L);

// 查找
int pos = search(&L, 20);
if (pos != -1)
printf("元素20的位置: %d\n", pos);
else
printf("未找到\n");

return 0;
}
