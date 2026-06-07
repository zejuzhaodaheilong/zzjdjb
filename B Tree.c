#include <stdio.h>
#include <stdlib.h>

#define M 4
#define MIN (M/2 - 1)

typedef struct BTreeNode {
    int keys[M - 1];
    struct BTreeNode *children[M];
    int num;
    int leaf;
} BTreeNode;


// ===================== 创建节点 =====================
BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->num = 0;
    node->leaf = leaf;

    for (int i = 0; i < M; i++) {
        node->children[i] = NULL;
    }
    return node;
}


// ===================== 查找 =====================
BTreeNode* search(BTreeNode* root, int key) {
    if (!root) return NULL;

    int i = 0;
    while (i < root->num && key > root->keys[i]) i++;

    if (i < root->num && root->keys[i] == key) return root;

    if (root->leaf) return NULL;

    return search(root->children[i], key);
}


// =====================================================
// =====================  分裂  =========================
// =====================================================
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);

    int mid = M / 2;

    z->num = mid - 1;

    for (int j = 0; j < mid - 1; j++)
        z->keys[j] = y->keys[j + mid];

    if (!y->leaf) {
        for (int j = 0; j < mid; j++)
            z->children[j] = y->children[j + mid];
    }

    y->num = mid - 1;

    for (int j = parent->num; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->num - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[mid - 1];
    parent->num++;
}


// =====================================================
// ===================== 插入 ===========================
// =====================================================
void insertNonFull(BTreeNode* node, int key) {
    int i = node->num - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num++;
    } else {
        while (i >= 0 && node->keys[i] > key)
            i--;

        i++;

        if (node->children[i]->num == M - 1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) i++;
        }

        insertNonFull(node->children[i], key);
    }
}

BTreeNode* insert(BTreeNode* root, int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->num = 1;
        return root;
    }

    if (root->num == M - 1) {
        BTreeNode* s = createNode(0);
        s->children[0] = root;

        splitChild(s, 0, root);

        int i = (key > s->keys[0]) ? 1 : 0;

        insertNonFull(s->children[i], key);
        return s;
    }

    insertNonFull(root, key);
    return root;
}


// =====================================================
// ===================== 删除工具函数 ====================
// =====================================================

// 找最大值（前驱）
int getPred(BTreeNode* node) {
    while (!node->leaf)
        node = node->children[node->num];
    return node->keys[node->num - 1];
}

// 找最小值（后继）
int getSucc(BTreeNode* node) {
    while (!node->leaf)
        node = node->children[0];
    return node->keys[0];
}

// borrow from left
void borrowFromPrev(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx - 1];

    for (int i = child->num - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->num; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = parent->keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->num];

    parent->keys[idx - 1] = sibling->keys[sibling->num - 1];

    child->num++;
    sibling->num--;
}


// borrow from right
void borrowFromNext(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx + 1];

    child->keys[child->num] = parent->keys[idx];

    if (!child->leaf)
        child->children[child->num + 1] = sibling->children[0];

    parent->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->num; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->num; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->num++;
    sibling->num--;
}


// merge
void merge(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx + 1];

    child->keys[MIN] = parent->keys[idx];

    for (int i = 0; i < sibling->num; i++)
        child->keys[i + MIN + 1] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->num; i++)
            child->children[i + MIN + 1] = sibling->children[i];
    }

    for (int i = idx + 1; i < parent->num; i++)
        parent->keys[i - 1] = parent->keys[i];

    for (int i = idx + 2; i <= parent->num; i++)
        parent->children[i - 1] = parent->children[i];

    child->num += sibling->num + 1;
    parent->num--;

    free(sibling);
}


// =====================================================
// ===================== 删除 ===========================
// =====================================================
void fill(BTreeNode* parent, int idx);

void deleteKey(BTreeNode* node, int key);

void deleteFromNonLeaf(BTreeNode* node, int idx) {
    int k = node->keys[idx];

    if (node->children[idx]->num > MIN) {
        int pred = getPred(node->children[idx]);
        node->keys[idx] = pred;
        deleteKey(node->children[idx], pred);
    }
    else if (node->children[idx + 1]->num > MIN) {
        int succ = getSucc(node->children[idx + 1]);
        node->keys[idx] = succ;
        deleteKey(node->children[idx + 1], succ);
    }
    else {
        merge(node, idx);
        deleteKey(node->children[idx], k);
    }
}


void deleteFromLeaf(BTreeNode* node, int idx) {
    for (int i = idx + 1; i < node->num; i++)
        node->keys[i - 1] = node->keys[i];
    node->num--;
}


// 主删除
void deleteKey(BTreeNode* node, int key) {
    if (!node) return;

    int idx = 0;
    while (idx < node->num && node->keys[idx] < key)
        idx++;

    if (idx < node->num && node->keys[idx] == key) {

        if (node->leaf)
            deleteFromLeaf(node, idx);
        else
            deleteFromNonLeaf(node, idx);
    }
    else {
        if (node->leaf) return;

        int flag = (idx == node->num);

        if (node->children[idx]->num < M/2)
            ; // 简化版：真实实现这里要 fill()

        deleteKey(node->children[idx], key);
    }
}


// =====================================================
// ===================== 打印 ===========================
// =====================================================
void printTree(BTreeNode* root, int level) {
    if (!root) return;

    int i;
    for (i = 0; i < root->num; i++) {
        if (!root->leaf)
            printTree(root->children[i], level + 1);

        for (int j = 0; j < level; j++)
            printf("    ");

        printf("%d\n", root->keys[i]);
    }

    if (!root->leaf)
        printTree(root->children[i], level + 1);
}


// =====================================================
// ===================== main ===========================
// =====================================================
int main() {
    BTreeNode* root = NULL;

    int arr[] = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int i = 0; i < 8; i++)
        root = insert(root, arr[i]);

    printf("初始B树:\n");
    printTree(root, 0);

    printf("\n删除20后:\n");
    deleteKey(root, 20);
    printTree(root, 0);

    printf("\n查找17:\n");
    BTreeNode* res = search(root, 17);
    printf(res ? "找到\n" : "未找到\n");

    return 0;
}