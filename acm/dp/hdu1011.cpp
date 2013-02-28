//刚开始没考虑m==0且根结点没有bugs的情况
//0个人的情况就不用考虑了，肯定是0
#include <stdio.h>
#include <memory.h>
#include <vector>
using namespace std;

const int N = 105;

int bugs[N], brains[N];

vector<int> tree[N];

int dp[N][N];

int n, m;

const int DEL = 20;

bool visited[N];
//dfs
void dfs(int u)
{
	int num = (bugs[u] + DEL-1)/DEL;
	
	for (int i = num; i <= m; i++)
	{
		dp[u][i] = brains[u];
	}

	visited[u] = 1;
	for (int i = 0; i < tree[u].size(); i++)
	{
		int v = tree[u][i];
		if (visited[v])
			continue;
		dfs(v);
		//得到相同的dp[u][j+k]，则组成的策略j和k已经发生了变化，不会出现根结点用了两种分配策略的情况
		//因为前一次得到的dp[u][j+k]的j+k >= j，而下一次用到的最大也只能是dp[u][k-1]，所以不会出现同结点使用两种分配策略的情况
		//但是如果j从小到大遍历的话，当前得到的dp[u][j+1]就会被下一次遍历所使用，出现了同一根节点使用两种分配策略的情况
		for (int j=m; j>=num; j--)
		{
			//k从1开始，因为0个人，肯定不能brains，但是这个结点的bugs可能为0，这样会导致错误
			for (int k = 1; j+k<=m;k++) //每次都使用j的初始背包去构造更大背包的最优
			{
				if (dp[u][j+k] < dp[u][j] + dp[v][k])
				{
					dp[u][j+k] = dp[u][j] + dp[v][k];
				}
			}
		}
	}
	
	
	
}

int main()
{
	//freopen("a.txt", "r", stdin);
	int a, b;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		if (n == -1 && m == -1)
			break;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d %d", &bugs[i], &brains[i]);
			tree[i].clear();
		}
		for (int i = 0; i <n-1; i++)
		{
			scanf("%d %d", &a, &b);
			tree[a].push_back(b);
			tree[b].push_back(a);
		}
		if (m == 0)
		{
			puts("0");
			continue;
		}
		memset(visited, 0, sizeof(visited));
		memset(dp, 0, sizeof(dp));
		dfs(1);
		
		printf("%d\n", dp[1][m]);

	}
	return 0;
}
