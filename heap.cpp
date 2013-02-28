#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//小根堆，把大的放到下面
void siftDown(int *a, int n, int i)    //n是只堆的长度，最后一个值的下标为n-1
{
    int key = a[i];
    int j = i;
    int k = 2*j+1;
    while(k<n)
    {
        if(k<n-1&&a[k]>a[k+1])
            k++;
        if(key > a[k])
        {
            swap(&a[j], &a[k]);
            j = k;
            k = 2*j+1;
        }
        else
        {
            break;
        }
    }
    a[j] = key;
}

void buildHeap(int *a, int n)
{
    for(int i=(n-2)/2; i>=0; i--)
    {
        siftDown(a, n, i);
    }
}

int main ( int argc, char *argv[] )
{
    freopen("data1", "r", stdin);
    int n;
    const int MAX = 101;
    int a[MAX];
    while(scanf("%d ", &n)!=EOF&&n)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d ", a+i);
        }
        buildHeap(a, n);
        for(int i=0; i<n-1; i++)
        {
            printf("%d ", a[i]);
        }
        printf("%d\n", a[n-1]);
    }
    
    return 0;
}

//两根指针，j指向上一个位置（需要替换的位置）
