#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;      // 存储数据
    int size;       // 当前元素个数
    int capacity;   // 当前容量
} SeqList;

/* 初始化顺序表 */
void InitList(SeqList* list, int initCapacity)
{
    list->data = (int*)malloc(sizeof(int) * initCapacity);

    if (list->data == NULL)
    {
        printf("内存申请失败\n");
        exit(1);
    }

    list->size = 0;
    list->capacity = initCapacity;
}

/* 扩容 */
void ExpandList(SeqList* list)
{
    int newCapacity = list->capacity * 2;

    int* newData = (int*)realloc(list->data,
                                 sizeof(int) * newCapacity);

    if (newData == NULL)
    {
        printf("扩容失败\n");
        exit(1);
    }

    list->data = newData;
    list->capacity = newCapacity;

    printf("扩容成功，当前容量：%d\n", newCapacity);
}

/* 尾插 */
void PushBack(SeqList* list, int value)
{
    // 判断是否需要扩容
    if (list->size >= list->capacity)
    {
        ExpandList(list);
    }

    list->data[list->size] = value;
    list->size++;
}

/* 删除指定位置元素 */
void Erase(SeqList* list, int pos)
{
    if (pos < 0 || pos >= list->size)
    {
        printf("删除位置非法\n");
        return;
    }

    for (int i = pos; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
}

/* 打印顺序表 */
void PrintList(SeqList* list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d ", list->data[i]);
    }

    printf("\n");
}

/* 销毁顺序表 */
void DestroyList(SeqList* list)
{
    free(list->data);

    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int main()
{
    SeqList list;

    // 初始容量为 3
    InitList(&list, 3);

    // 插入数据
    for (int i = 1; i <= 10; i++)
    {
        PushBack(&list, i);
    }

    printf("顺序表内容：\n");
    PrintList(&list);

    // 删除下标为 2 的元素
    Erase(&list, 2);

    printf("删除后：\n");
    PrintList(&list);

    // 释放内存
    DestroyList(&list);

    return 0;
}
