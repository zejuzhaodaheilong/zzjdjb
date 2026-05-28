#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int weight;
    int parent;
    int lchild;
    int rchild;
} HTNode;

typedef char* HuffmanCode[MAX];


// 选出 parent 为 0 的两个最小权值结点
void selectMin(HTNode ht[], int n, int *s1, int *s2) {
    int min1 = 1000000;
    int min2 = 1000000;

    *s1 = *s2 = -1;

    for (int i = 1; i <= n; i++) {

        if (ht[i].parent == 0) {

            if (ht[i].weight < min1) {

                min2 = min1;
                *s2 = *s1;

                min1 = ht[i].weight;
                *s1 = i;
            }
            else if (ht[i].weight < min2) {

                min2 = ht[i].weight;
                *s2 = i;
            }
        }
    }
}


// 创建哈夫曼树
void createHuffmanTree(HTNode ht[], int n) {

    int m = 2 * n - 1;

    // 初始化所有结点
    for (int i = 1; i <= m; i++) {

        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].rchild = 0;
    }

    // 构造非叶子结点
    for (int i = n + 1; i <= m; i++) {

        int s1, s2;

        selectMin(ht, i - 1, &s1, &s2);

        ht[s1].parent = i;
        ht[s2].parent = i;

        ht[i].lchild = s1;
        ht[i].rchild = s2;

        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
}


// 生成哈夫曼编码
void createHuffmanCode(HTNode ht[], HuffmanCode hc, int n) {

    char cd[MAX];

    cd[n - 1] = '\0';

    for (int i = 1; i <= n; i++) {

        int start = n - 1;

        int c = i;
        int p = ht[c].parent;

        while (p != 0) {

            if (ht[p].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';

            c = p;
            p = ht[c].parent;
        }

        hc[i] = (char*)malloc((n - start) * sizeof(char));

        strcpy(hc[i], &cd[start]);
    }
}


// 前序遍历
void preorder(HTNode ht[], int root) {

    if (root == 0)
        return;

    printf("%d ", ht[root].weight);

    preorder(ht, ht[root].lchild);
    preorder(ht, ht[root].rchild);
}


int main() {

    int n = 5;

    int w[6] = {0, 5, 9, 12, 13, 16};

    HTNode ht[2 * MAX];

    HuffmanCode hc;

    // 初始化叶子结点
    for (int i = 1; i <= n; i++) {

        ht[i].weight = w[i];

        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].rchild = 0;
    }

    // 创建哈夫曼树
    createHuffmanTree(ht, n);

    // 创建哈夫曼编码
    createHuffmanCode(ht, hc, n);

    // 输出编码
    printf("哈夫曼编码：\n");

    for (int i = 1; i <= n; i++) {

        printf("权值 %d 的编码：%s\n", ht[i].weight, hc[i]);
    }

    // 前序遍历
    printf("\n前序遍历（权值）：\n");

    preorder(ht, 2 * n - 1);

    printf("\n");

    return 0;
}
