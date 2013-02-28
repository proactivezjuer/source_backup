include <iostream>
#include <cmath>
using namespace std;
const int MAX=105;
double a[MAX][MAX], b[MAX], x[MAX];
bool flag;
int m,n;
const double EXP=1e-10;
int num;

//又是高斯方程写错了，以后一定要反思了
void guass()
{
    flag = 1;

    int k, i, index, j;
    double maxi, d;

    for (k = 0; k < num; k++)    
    {
        maxi = 0;

        for (i = k; i < num; i++)    
        {
            if (fabs(a[i][k]) > maxi)    
            {
                index = i;
                maxi = fabs(a[i][k]);
            }
        }

        if (maxi < EXP)
        {
            flag = 0;
            return;
        }

        if (index != k)        
        {
            //整个晚上都在wa，就是因为这里写错了或者没有写
            //说明高斯函数还是写得不够熟啊
            double temp = b[index];
            b[index] = b[k];
            b[k] = temp;

            for (i = 0; i < num; i++)
            {
                temp = a[index][i];
                a[index][i] = a[k][i];
                a[k][i] = temp;
            }
        }

        for (i = k + 1; i < num; i++)        
        {
            d = a[i][k] / a[k][k];
            b[i] -= b[k] * d;
            a[i][k] = 0;

            for (j = k + 1; j < num; j++)
                a[i][j] -= a[k][j] * d;

        }
    }

    for (i = num - 1; i >= 0; i--)        
    {
        for (j = i + 1; j < num; j++)
        {
            b[i] -= a[i][j] * x[j];
        }

        x[i] = b[i] / a[i][i];
    }
}


int main()
{
    //freopen("a.txt", "r", stdin);
    while (scanf("%d %d ",&m,&n)!=EOF)
    {
        if(n&1)
        {
            n=m-n;
        }
        if(n&1)
        {
            puts("INF");
            continue;
        }
        memset(a, 0, sizeof(a));
        a[0][0]=1;
        b[0]=0;
        num=1;
        for(int i=2; i+3<=m; i+=2)
        {
            a[num][i>>1] = 2;
            a[num][(i+2)>>1]=-1;
            a[num][(i-2)>>1]=-1;
            b[num]=4;
            num++;
        }
        if(m&1)
        {
            a[num][(m-1)>>1]=1;
            a[num][(m-3)>>1]=-1;
            b[num]=4;
            num++;
        }    
        else
        {
            a[num][(m-2)>>1]=2;
            a[num][(m-4)>>1]=-1;
            b[num]=4;
            num++;
        }
        guass();
        if(flag)
        {
            printf("%.2lf\n", x[n>>1]);
        }
        else
        {
            puts("INF");
        }
    }
    return 0;
}
