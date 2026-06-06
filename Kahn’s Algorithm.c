#include <stdio.h>

#define N 4   // 图中有4个顶点

int main()
{
    // 邻接矩阵
    // A→B
    // A→C
    // B→D
    // C→D
    int graph[N][N] =
    {
        {0,1,1,0}, // A
        {0,0,0,1}, // B
        {0,0,0,1}, // C
        {0,0,0,0}  // D
    };

    int indegree[N] = {0}; // 存储每个顶点的入度

    int queue[N];          // 模拟队列
    int front = 0;         // 队头下标（从这里取元素）
    int rear = 0;          // 队尾下标（往这里放元素）

    // =========================
    // 第一步：统计入度
    // =========================
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(graph[i][j] == 1)
            {
                indegree[j]++;
            }
        }
    }

    // 此时：
    // indegree[0] = 0  A
    // indegree[1] = 1  B
    // indegree[2] = 1  C
    // indegree[3] = 2  D

    // =========================
    // 第二步：入度为0的顶点入队
    // =========================
    for(int i = 0; i < N; i++)
    {
        if(indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    // 此时：
    // queue[0] = 0 (A)
    // front = 0
    // rear = 1

    printf("拓扑排序结果：");

    // =========================
    // 第三步：开始处理队列
    // =========================
    while(front < rear)
    {
        // 取出队头元素
        int u = queue[front++];

        // 输出当前顶点
        printf("%c ", 'A' + u);

        // 遍历u的所有邻接点
        for(int v = 0; v < N; v++)
        {
            if(graph[u][v] == 1)
            {
                // 删除边的影响
                indegree[v]--;

                // 如果入度变成0
                if(indegree[v] == 0)
                {
                    queue[rear++] = v;
                }
            }
        }
    }

    return 0;
}