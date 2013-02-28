#include <stdio.h>

int partition(int *a, int st, int ed)
{
    int key = a[st];
    while(st<ed)
    {
        while(st<ed&&a[ed]>=key)
        {
            ed--;
        }
        if(a[ed]<key)
        {
            a[st] = a[ed];
            st++;
        }
        while(st<ed&&a[st]<key)
        {
            st++;
        }
        if(a[st]>=key)
        {
            a[ed] = a[st];
            ed--;
        }
    }
    a[st] = key;
    return st;
}

void qsort(int *a, int st, int ed)
{
    if(st<ed)
    {
        int pos = partition(a, st, ed);
        qsort(a, st, pos-1);
        qsort(a, pos+1, ed);
    }
}


int main ( int argc, char *argv[] )
{
    freopen("data", "r", stdin);
    int n;
    const int MAX = 101;
    int a[MAX];
    while(scanf("%d ", &n)!=EOF&&n)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d ", a+i);
        }
        qsort(a, 0, n-1);
        for (int i=0; i<n-1; i++)
        {
            printf("%d ", a[i]);
        }
        printf("%d\n", a[n-1]);
        
    }
    return 0;
}

//初始位置值赋值给一个变量，然后后面的值覆盖前面的值，到达了最后的位置，然后重新把变量的赋值回去，和堆的思想一样
