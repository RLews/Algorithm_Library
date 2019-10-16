#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SORT_DATA_LEN           10u

typedef int SortData_t;
typedef long SortDatLen_t;

static const SortData_t SortDataSrc[SORT_DATA_LEN] = {
    1, -99, 123, 32, 36, -10, 12, -19, 199, 233
};


static void Sort_HeapPercDown(SortData_t pDat[], SortDatLen_t p, SortDatLen_t n);
static void Sort_SwapData(SortData_t *a, SortData_t *b);

static SortDatLen_t Sort_QuickFindPos(SortData_t pDat[], SortDatLen_t low, SortDatLen_t high);

static void Sort_DebugPrint(const SortData_t pBuf[], SortDatLen_t n);


/*!
    @brief 交换数据
*/
static void Sort_SwapData(SortData_t *a, SortData_t *b)
{
    if ((a == NULL) || (b == NULL))
    {
        return;
    }

    SortData_t t = *a;

    *a = *b;
    *b = t;
}

/*!
    @brief 将N个元素的数组以P为跟节点的子堆调整为最大堆
*/
static void Sort_HeapPercDown(SortData_t pDat[], SortDatLen_t p, SortDatLen_t n)
{
    SortDatLen_t tParent = 0;
    SortDatLen_t tChild = 0;
    SortData_t temp = 0;

    if (pDat == NULL)
    {
        return;
    }

    temp = pDat[p]; //取出根节点
    for (tParent = p; ((tParent * 2) + 1) < n; tParent = tChild)
    {
        tChild = (tParent * 2) + 1;
        if ( (tChild != (n - 1)) && (pDat[tChild] < pDat[tChild+1]) )
        {
            tChild++; //child指向左右子节点的较大者
        }

        if (temp >= pDat[tChild])
        {
            break; //找到了合适位置
        }
        else
        {
            pDat[tParent] = pDat[tChild];
        }
    }
    pDat[tParent] = temp;
}

/*!
    @brief 堆排序
*/
void Sort_Heap(SortData_t pDat[], SortDatLen_t n)
{
    SortDatLen_t i = 0;

    for (i = (n / 2) - 1; i >= 0; i--)
    {
        Sort_HeapPercDown(pDat, i, n);
    }

    for (i = n - 1; i > 0; i--)
    {
        Sort_SwapData(&pDat[0], &pDat[i]);
        Sort_HeapPercDown(pDat, 0, i);
    }
}

/*!
    @brief 取最低索引，将小于自身的放入左边，其他的放入右边
    3   5   2   4   1   3       temp = 3
    L                   H

    1   2   3   4   5   3
*/
static SortDatLen_t Sort_QuickFindPos(SortData_t pDat[], SortDatLen_t low, SortDatLen_t high)
{
    SortData_t temp = 0;

    if (pDat == NULL)
    {
        return high;
    }

    temp = pDat[low];
    while (low < high)
    {
        while ((low < high) && (pDat[high] >= temp))
        {
            high--;
        }
        pDat[low] = pDat[high];

        while ((low < high) && (pDat[low] <= temp))
        {
            low++;
        }
        pDat[high] = pDat[low];
    }
    pDat[low] = temp;

    return high;
}

/*!
    @brief 快速排序
*/
void Sort_Quick(SortData_t pDat[], SortDatLen_t low, SortDatLen_t high)
{
    SortDatLen_t pos = 0;

    if (pDat == NULL)
    {
        return;
    }

    if (low < high)
    {
        pos = Sort_QuickFindPos(pDat, low, high);
        Sort_Quick(pDat, low, pos - 1);
        Sort_Quick(pDat, pos + 1, high);
    }
}

static void Sort_DebugPrint(const SortData_t pBuf[], SortDatLen_t n)
{
    SortDatLen_t i = 0;

    printf("Sort Data : ");
    for (i = 0; i < n; i++)
    {
        printf(" %d ", pBuf[i]);
    }
    printf("\n");
}

int main()
{
    SortData_t heapSortRes[SORT_DATA_LEN] = {0};
    SortData_t quickSortRes[SORT_DATA_LEN] = {0};

    memcpy(heapSortRes, SortDataSrc, SORT_DATA_LEN * sizeof(SortData_t));
    memcpy(quickSortRes, SortDataSrc, SORT_DATA_LEN * sizeof(SortData_t));

    Sort_Heap(heapSortRes, SORT_DATA_LEN);
    printf("Heap Sort Output : \n");
    Sort_DebugPrint(heapSortRes, SORT_DATA_LEN);

    Sort_Quick(quickSortRes, 0, SORT_DATA_LEN - 1);
    printf("Quick Sort Output : \n");
    Sort_DebugPrint(quickSortRes, SORT_DATA_LEN);

    return 0;
}
