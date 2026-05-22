#include <stdio.h>

#define N 6

// 图的邻接矩阵
int graph[N][N] = {
   {0,1,1,0,0,0},
   {1,0,0,1,1,0},
   {1,0,0,0,0,1},
   {0,1,0,0,0,0},
   {0,1,0,0,0,0},
   {0,0,1,0,0,0}
};

int visited[N];

// 深度优先搜索
void dfs(int v)
{
   printf("%d ", v);
   
   visited[v] = 1;
   
   for(int i = 0; i < N; i++)
   {
      if(graph[v][i] == 1 && !visited[i])
      {
         dfs(i);
      }
   }
}

int main()
{
   dfs(0);
   
   return 0;
}
