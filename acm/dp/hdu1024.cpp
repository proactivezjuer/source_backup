#include <stdio.h>
const int N=1000005;
int a[N],dp[N],f[2][N],sum[N];
int n,m;
const int INIT=-2000000000;


int main()
{
	//freopen("a.txt","r",stdin);
	while(scanf("%d %d ",&m,&n)!=EOF)
	{
		sum[0]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d ",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}
		dp[0]=0;
		f[0][0]=0;
		f[1][0]=0;
		for(int i=1;i<=n;i++)
		{
			//用f[0][j]进行比较，用f[1][j]进行动态变化
			//因为每次比较都需要用到以前最佳的，而又需要保留现在最佳的
			//因为以前还没有初始化f[1][i]，这里需要把它初始化成负无穷
			f[1][i]=INIT;
			for(int j=1;j<=i&&j<=m;j++)
			{
				if(j==i)
				{
					dp[j]=sum[j];
				}
				else
				{
					//这里不会出现没有初始化dp[j]的情况，因为j==i已经在上面的if语句里处理了
					if(dp[j]>f[0][j-1])
					{
						dp[j]=dp[j]+a[i];
					}
					else
					{
						dp[j]=f[0][j-1]+a[i];
					}
				}
				//f[1][j]用于动态更新
				if(dp[j]>f[1][j])
				{
					f[1][j]=dp[j];
				}
			}


			for(int j=1;j<=i&&j<=m;j++)
			{
				f[0][j]=f[1][j];
			}
		}

		printf("%d\n",f[1][m]);
	}
	return 0;
}

