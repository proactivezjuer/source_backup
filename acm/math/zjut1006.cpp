//poj2279上能够过，这里使用的是钩子函数
#include <iostream>
using namespace std;
const int N=11;
const int M=31;
bool a[N][M];
int b[N];
unsigned __int64 c[M];
unsigned __int64 fac[M];
int k,n;

unsigned __int64 gcd(unsigned __int64 a,unsigned __int64 b)
{
    unsigned __int64 t;
    while(b!=0)
    {
        t=a;
        a=b;
        b=t%a;
    }
    return a;
}


int main()
{
    //freopen("a.txt","r",stdin);
    while(scanf("%d ",&k)!=EOF&&k)
    {
        n=0;
        memset(a,0,sizeof(a));
        for(int i=0;i<M;i++)
        {
            c[i]=1;
        }
        for(int i=0;i<k;i++)
        {
            scanf("%d ",&b[i]);
            for(int j=0;j<b[i];j++)
            {
                a[i][j]=1;
            }
            n+=b[i];
        }
        if(k==1)
        {
            puts("1");
            continue;
        }
        int cnt=0;
        for(int i=0;i<k;i++)
        {
            for(int j=0;a[i][j]!=0;j++)
            {
                for(int l=j+1;a[i][l]!=0;l++)
                {
                    c[cnt]++;
                }
                for(int l=i+1;a[l][j]!=0;l++)
                {
                    c[cnt]++;
                }
                cnt++;
            }
        }
        for(int i=1;i<=n;i++)
        {
            fac[i]=i;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=n;j>=1;j--)
            {
                if(c[i]==1)
                {
                    break;
                }
                else
                {
                    unsigned __int64 d=gcd(fac[j],c[i]);
                    fac[j]/=d;
                    c[i]/=d;
                }
            }
        }
        unsigned __int64 res=1;
        for(int i=1;i<=n;i++)
        {
            res*=fac[i];
        }
        printf("%I64u\n",res);
    }
    return 0;
}
