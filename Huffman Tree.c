#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HTNode;

typedef char* HuffmanCode[MAX];

void selectMin(HTNode ht[],int n,int*s1,int*s2){
    int min1 = 1e9,min2 = 1e9;
    int i;
    
    *s1 = *s2 = -1;
    for(i = 1;i <= n;i++){
        if(ht[i].parent == 0){
            if(ht[i].weight < min){
                min2 = min1;*s2 = *s1;
                min1 = ht[i].weight;*s = i;
            }else if(ht[i].weight < min2){
                min2 = ht[i].weight;*s2 = i;
                
            }
        }
    }
}

void createHuffmanTree(HTNode ht[],int n){
    int m = 2*n - 1;
    int i;
    
    for(i = 1;i < m;i++){
        ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }
    for(i = n + 1;i <= m;i++){
        int s1,s2;
        selectMin(ht,i - 1,&s1,&s2);
        
        ht[s1].parent = i;
        ht[s2].parent = i;
        
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
}

void createHuffmanCode(HTNode ht[],HuffmanCode hc,int n){
    char cd[MAX];
    cd[n - 1] = '\0';
    
    for(int i = 1;i < n;i++){
        int start = n - 1;
        int c = i;
        int p = ht[c].parent;
        
        while(p != 0){
            if(ht[p].lchild == c)
            cd[--start] = '0';
            else
                cd[--start] = '1';
                    
                    c = p;
                    p = ht[c].parent;
                }
                hc[i] = (char*)malloc((n - start)*sizeof(char));
                strcpy(hc[i],&cd[start]);
            }
        }
        
        void preorder(HTNode ht[],int root){
            if(root == 0)return;
            printf("%d",ht[root].weight);
            preorder(ht,ht[root].lchild);
            preorder(ht,ht[root].rchild);
        }
        
        int main(){
            int n = 5;
            int w[6] = {0,5,9,12,13,16};
            
            HTNode ht[2*MAX];
            HUffmanCode hc;
            
            for(int i = 1;i <= n;i++){
                ht[i].weight = w[i];
                ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
            }
            
            createHuffmanTree(ht,n);
            createHuffmanCode(ht,hc,n);
            printf("哈夫曼编码：\n");
            for(int i = 1;i <= n;i++){
                printf("权值%d的编码：%s\n",ht[i].weight,hc[i]);
            }
            
            printf("\前序遍历（权值）：\n");
            preorder(ht,2*n - 1);
            
            return 0;
        }
        
  
