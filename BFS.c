#include <stdio.h>
#include <stdlib.h>

// 二叉树结点定义
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

// 创建新结点
TreeNode* createNode(int value)
{
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 广度优先遍历 BFS
void BFS(TreeNode *root)
{
    if(root == NULL)
        return;

    // 定义队列
    TreeNode *queue[100];

    int front = 0;
    int rear = 0;

    // 根节点入队
    queue[rear++] = root;

    // 队列不为空时循环
    while(front < rear)
    {
        // 出队
        TreeNode *current = queue[front++];

        // 输出当前结点
        printf("%d ", current->data);

        // 左孩子入队
        if(current->left != NULL)
        {
            queue[rear++] = current->left;
        }

        // 右孩子入队
        if(current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

// 主函数
int main()
{
    /*
            1
          /   \
         2     3
        / \   / \
       4  5  6  7
    */

    TreeNode *root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("广度优先遍历结果：");

    BFS(root);

    return 0;
}