#include <stdio.h>

// 调整为大顶堆
void heapify(int arr[], int n, int i)
{
    int largest = i;       // 当前最大元素下标
    int left = 2 * i + 1;  // 左孩子
    int right = 2 * i + 2; // 右孩子

    // 找出父节点和左孩子中较大的
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // 找出当前最大值和右孩子中较大的
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // 如果最大值不是父节点
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 继续向下调整
        heapify(arr, n, largest);
    }
}

// 建立大顶堆
void buildHeap(int arr[], int n)
{
    // 从最后一个非叶子节点开始
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

// 堆排序
void heapSort(int arr[], int n)
{
    // 第一步：建堆
    buildHeap(arr, n);

    // 第二步：不断把堆顶放到最后
    for (int i = n - 1; i > 0; i--)
    {
        // 堆顶与最后一个元素交换
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 重新调整剩余元素
        heapify(arr, i, 0);
    }
}

// 打印数组
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {4, 8, 6, 2, 9, 1, 7, 3, 5};

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("排序前：\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("排序后：\n");
    printArray(arr, n);

    return 0;
}