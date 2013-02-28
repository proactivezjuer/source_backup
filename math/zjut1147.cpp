#include <stdio.h>
#include <memory.h>
#define N 9        //二维数组每一维的最大
int a[N][N];    //记录Pi(非5的倍数)和2^y的各位分别为x和y时，那么Pi(非5的倍数)/2^y的个位数是多少，这个很容易推导
int b[4];    //2^k的尾数，因为4个开始循环了
int c[10];    //c[remian]的值直接打印出来
void init()    //初始化a数组
{
    memset(a, 0, sizeof(a));
    a[2][2]=6;
    a[2][4]=8;
    a[2][6]=2;
    a[2][8]=4;
    a[4][2]=2;
    a[4][4]=6;
    a[4][6]=4;
    a[4][8]=8;
    a[6][2]=8;
    a[6][4]=4;
    a[6][6]=6;
    a[6][8]=2;
    a[8][2]=4;
    a[8][4]=2;
    a[8][6]=8;
    a[8][8]=6;
    b[0] = 6;
    b[1] = 2;
    b[2] = 4;
    b[3] = 8;
    c[0] = 1;
    c[1] = 1;
    c[2] = 2;
    c[3] = 6;
    c[4] = 4;
    c[5] = 4;
    c[6] = 4;
    c[7] = 8;
    c[8] = 4;
    c[9] = 6;
}

int solve(int n)
{
    if(n<5)
    {
        int res = 1;
        for(int i=2; i<=n; i++)
        {
            res*=i;
        }
        return res%10;
    }
    int remain = n%10;
    int st = c[remain];
    if(n>=10)
    {
        st = (st*6)%10;
    }
    int ed = b[(n/5)%4];
    int res1 = a[st][ed];
    return (res1*solve(n/5))%10;

}


int main ( int argc, char *argv[] )
{
    freopen("data", "r", stdin);
    init();
    int n;    
    while(scanf("%d ", &n)!=EOF&&n)
    {
        printf("%d\n", solve(n));
    }
    return 0;
}
