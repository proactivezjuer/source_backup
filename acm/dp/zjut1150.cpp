//dp[i][j]=maxv(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) (1)
//a[i]==b[x]&&b[j]==a[y]&&a[i]!=b[j]&&x<i&&y<j，则dp[i][j]=maxv(dp[i][j],2+dp[x-1][y-1]) (2)
//因为不存在两条线段从同一个点出发，所以有dp[x-1][y-1]
//因为x和y都可能等于第一个数的下标，所以下标不能从0开始，而应该从1开始
//dp[i][j]表示从a[1..i]和b[1..j]存在的匹配的个数
//条件1指出一条线段只能和另一条线段相交，而不能同多余一条的线段相交，所以有(2)成立

#include<stdio.h>
#include <memory.h>

const int N=101;
int a[N],b[N],dp[N][N];
int n1,n2;

int maxv(int x, int y, int z)
{
	int mv=x;
	if(y>mv)
	{
		mv=y;
	}
	if(z>mv)
	{
		mv=z;
	}
	return mv;
}

int main()
{
	//freopen("a.txt","r",stdin);
	while(scanf("%d %d ",&n1,&n2)!=EOF)
	{
		//输入上一行，下标从1开始，因为0下标当做一个虚拟的参考
		for(int i=1;i<=n1;i++)
		{
			scanf("%d ",a+i);
		}
		//输入下一行
		for(int i=1;i<=n2;i++)
		{
			scanf("%d ",b+i);
		}
		//memset指定的位数，因为最多用到(n1+1)*(n2+1)个int型
		memset(dp,0,((n1+1)*(n2+1))<<2);

		//a[1..i]和b[1..j]之间交叉匹配的个数，并且记录在dp[i][j]中
		//因为i=1时，1..1总共才1个数，不可能形成交叉匹配，所以肯定为0
		//同理j=1时，所以i和j的下标直接从2开始
		for(int i=2;i<=n1;i++)
		{
			for(int j=2;j<=n2;j++)
			{
				dp[i][j]=maxv(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);

				//因为交叉匹配的时候a!=b，所以如果a==b就不需要寻找交叉匹配部分
				if(a[i]==b[j])
				{
					continue;
				}

				//寻找可能的b[x]==a[i]和a[y]==b[j]且x<j且y<i
				int x,y;
				//因为x<j，下标从1开始，所以有x>=1，如果有x==0说明没有找到
				for(x=j-1;x>=1;x--)
				{
					if(a[i]==b[x])
					{
						break;
					}
				}
				//因为y<i，下标从1开始，所以有y>=1，如果有y==0说明没有找到
				for(y=i-1;y>=1;y--)
				{
					if(a[y]==b[j])
					{
						break;
					}
				}
				//x和y都不为0，说明找到了a[i]==b[x]和a[y]==b[j]
				//fuck,把x和y的位置换错了，x对应的是b数组，而y对应的是a数组，这些小细节一定要十分小心
				if(x&&y)
				{
					if(dp[i][j]<dp[y-1][x-1]+2)
					{
						dp[i][j]=dp[y-1][x-1]+2;
					}
				}
			}
		}
		//最后输出dp[n1][n2]即为结果
		printf("%d\n",dp[n1][n2]);
	}
	return 0;
}
