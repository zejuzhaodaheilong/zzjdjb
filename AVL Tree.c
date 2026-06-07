#include <stdio.h>
#include <stdlib.h>

// AVL树结点
typedef struct AVLNode
{
    int data;                  // 数据域
    int height;                // 结点高度
    struct AVLNode *lchild;    // 左孩子
    struct AVLNode *rchild;    // 右孩子
}AVLNode;


// 求最大值
int Max(int a,int b)
{
    return a>b?a:b;
}


// 获取结点高度
int Height(AVLNode *T)
{
    if(T==NULL)
        return 0;

    return T->height;
}


// 创建新结点
AVLNode* CreateNode(int key)
{
    AVLNode *node=(AVLNode*)malloc(sizeof(AVLNode));

    node->data=key;
    node->height=1;

    node->lchild=NULL;
    node->rchild=NULL;

    return node;
}


// 计算平衡因子
int GetBalance(AVLNode *T)
{
    if(T==NULL)
        return 0;

    return Height(T->lchild)-Height(T->rchild);
}


// 右旋（处理LL）
AVLNode* RightRotate(AVLNode *y)
{
    AVLNode *x=y->lchild;
    AVLNode *T2=x->rchild;

    // 旋转
    x->rchild=y;
    y->lchild=T2;

    // 更新高度
    y->height=
        Max(Height(y->lchild),
            Height(y->rchild))+1;

    x->height=
        Max(Height(x->lchild),
            Height(x->rchild))+1;

    return x;
}


// 左旋（处理RR）
AVLNode* LeftRotate(AVLNode *x)
{
    AVLNode *y=x->rchild;
    AVLNode *T2=y->lchild;

    // 旋转
    y->lchild=x;
    x->rchild=T2;

    // 更新高度
    x->height=
        Max(Height(x->lchild),
            Height(x->rchild))+1;

    y->height=
        Max(Height(y->lchild),
            Height(y->rchild))+1;

    return y;
}


// AVL插入
AVLNode* Insert(AVLNode *T,int key)
{
    // 1. 按BST方式插入
    if(T==NULL)
        return CreateNode(key);

    if(key<T->data)
        T->lchild=Insert(T->lchild,key);

    else if(key>T->data)
        T->rchild=Insert(T->rchild,key);

    else
        return T;


    // 2. 更新高度
    T->height=
        1+Max(
              Height(T->lchild),
              Height(T->rchild)
             );


    // 3. 获取平衡因子
    int balance=GetBalance(T);


    // 4. LL
    if(balance>1 &&
       key<T->lchild->data)
    {
        return RightRotate(T);
    }


    // 5. RR
    if(balance<-1 &&
       key>T->rchild->data)
    {
        return LeftRotate(T);
    }


    // 6. LR
    if(balance>1 &&
       key>T->lchild->data)
    {
        T->lchild=
            LeftRotate(T->lchild);

        return RightRotate(T);
    }


    // 7. RL
    if(balance<-1 &&
       key<T->rchild->data)
    {
        T->rchild=
            RightRotate(T->rchild);

        return LeftRotate(T);
    }

    return T;
}


// 中序遍历
void InOrder(AVLNode *T)
{
    if(T)
    {
        InOrder(T->lchild);

        printf("%d ",T->data);

        InOrder(T->rchild);
    }
}


// 主函数
int main()
{
    AVLNode *root=NULL;

    root=Insert(root,10);
    root=Insert(root,20);
    root=Insert(root,30);
    root=Insert(root,40);
    root=Insert(root,50);
    root=Insert(root,25);

    printf("中序遍历：");

    InOrder(root);

    printf("\n");

    return 0;
}