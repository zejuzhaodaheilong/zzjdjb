#include <stdio.h>
#include <stdlib.h>

// 二叉排序树结点
typedef struct BSTNode
{
    int data;                  // 数据域
    struct BSTNode *lchild;    // 左孩子
    struct BSTNode *rchild;    // 右孩子
}BSTNode;


// 创建新结点
BSTNode* CreateNode(int x)
{
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));

    node->data = x;
    node->lchild = NULL;
    node->rchild = NULL;

    return node;
}


// 插入结点
BSTNode* Insert(BSTNode *root, int x)
{
    // 找到空位置
    if(root == NULL)
    {
        return CreateNode(x);
    }

    // 插入左子树
    if(x < root->data)
    {
        root->lchild = Insert(root->lchild, x);
    }

    // 插入右子树
    else if(x > root->data)
    {
        root->rchild = Insert(root->rchild, x);
    }

    return root;
}


// 查找结点
BSTNode* Search(BSTNode *root, int key)
{
    if(root == NULL)
    {
        return NULL;
    }

    if(root->data == key)
    {
        return root;
    }

    if(key < root->data)
    {
        return Search(root->lchild, key);
    }
    else
    {
        return Search(root->rchild, key);
    }
}


// 中序遍历
void InOrder(BSTNode *root)
{
    if(root != NULL)
    {
        InOrder(root->lchild);

        printf("%d ", root->data);

        InOrder(root->rchild);
    }
}


int main()
{
    BSTNode *root = NULL;

    // 插入数据
    root = Insert(root, 50);
    root = Insert(root, 30);
    root = Insert(root, 70);
    root = Insert(root, 20);
    root = Insert(root, 40);
    root = Insert(root, 60);
    root = Insert(root, 80);

    printf("中序遍历结果：\n");
    InOrder(root);

    printf("\n");

    // 查找
    int key = 60;

    BSTNode *p = Search(root, key);

    if(p != NULL)
    {
        printf("找到结点：%d\n", p->data);
    }
    else
    {
        printf("未找到\n");
    }

    return 0;
}