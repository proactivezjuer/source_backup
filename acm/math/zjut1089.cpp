#include <stdio.h>
const int N=1501;
int a[N]={0,1,2,3,4,5};
int b[3]={2,3,5};
int c[3]={3,2,2};


void init()
{
    for(int i=6;i<N;i++)
    {
        int temp=b[0]*a[c[0]];
        for(int j=1;j<3;j++)
        {
            if(temp>b[j]*a[c[j]])
            {
                temp=b[j]*a[c[j]];
            }
        }
        a[i]=temp;
        for(int j=0;j<3;j++)
        {
            if(temp==b[j]*a[c[j]])
            {
                c[j]++;
            }
        }
    }
}

int main()
{
    //freopen("a.txt","r",stdin);
    init();
    int n;
    while(scanf("%d ",&n)!=EOF)
    {
        printf("The %dth ugly number is %d.\n",n,a[n]);
    }
    
    return 0;
}
