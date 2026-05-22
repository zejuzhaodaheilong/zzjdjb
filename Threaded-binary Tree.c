#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义线索二叉树节点
typedef struct ThreadNode {
    char data;                 // 节点数据
    struct ThreadNode *lchild, *rchild; // 左右指针
    int ltag, rtag;            // 标签：0=孩子，1=线索
} ThreadNode;

// 全局前驱指针，用于线索化
ThreadNode *pre = NULL;

// 创建新节点
ThreadNode* createNode(char val) {
    ThreadNode *node = (ThreadNode*)malloc(sizeof(ThreadNode));
    node->data = val;
    node->lchild = node->rchild = NULL;
    node->ltag = node->rtag = 0;
    return node;
}

// 中序线索化函数
void inThread(ThreadNode *root) {
    if (root == NULL) return;
    
    // 左子树线索化
    inThread(root->lchild);
    
    // 处理当前节点
    if (root->lchild == NULL) {
        root->ltag = 1;     // 左线索
        root->lchild = pre; // 指向前驱
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rtag = 1;      // 右线索
        pre->rchild = root; // 前驱的后继是当前节点
    }
    pre = root;             // 更新前驱
    
    // 右子树线索化
    inThread(root->rchild);
}

// 中序遍历线索二叉树
void inOrderTraverse(ThreadNode *root) {
    ThreadNode *p = root;
    while (p != NULL) {
        // 找到最左下节点
        while (p->ltag == 0) //这个循环可以一直走直到达到二叉树的左下角
        p = p->lchild;
        
        // 输出节点
        printf("%c ", p->data);
        
        // 顺着线索向后走
        while (p->rtag == 1 && p->rchild != NULL) { //这里只有遍历到最后一个节点的时候才会出现rtag==1且rchild==NULL                                                                      
            p = p->rchild;
            printf("%c ", p->data);
        }
        
        // 移动到右子树
        p = p->rchild;
    }
}

// 构建示例二叉树
ThreadNode* createExampleTree() {
    ThreadNode *A = createNode('A');
    ThreadNode *B = createNode('B');
    ThreadNode *C = createNode('C');
    ThreadNode *D = createNode('D');
    ThreadNode *E = createNode('E');
    
    A->lchild = B;
    A->rchild = C;
    B->rchild = D;
    D->rchild = E;
    
    return A; // 返回根节点
}

int main() {
    ThreadNode *root = createExampleTree(); //root只储存的树的起点（根），通过它就可以访问整棵树，这个操作相当于把两个同类型，A=root 
    
    // 中序线索化
    pre = NULL;
    inThread(root);
    
    printf("中序遍历线索二叉树: ");
    inOrderTraverse(root);
    printf("\n");
    
    return 0;
}


/*线索二叉树的遍历：
      A
    /   \
   B     C
  / \   / \
 D   E F   G
/ \
H  I
    \
     J
这里按上面inorderTraverse中序遍历二叉树，先是从A->B->D->H，然后就会输出H,这个时候rtag==1 && rchild ！= NULL，p就会根据线索（p = p->rchild)跳回D,然后输出D，再(p = p->rchild)从D跳到I，此时大循环完成了一次，这时候从I开始重新进行一次大循环，因为I没有左孩子，因此不执行第一个循环直接输出I，再判断第二个循环，符合，p从I跳到J，最后执行最后一步（p = p->rchild)根据线索p就从J跳到了B，再开始下一步的大循环，后续都像这样。*/    
