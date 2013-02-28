#include<vector>
#include<map>
#include<queue>
#include<memory.h>
#include <stdio.h>
using namespace std;
//最大的顶点数
const int N=1001;
//用于并查集的数组，如果是根有pre[i]=i
int pre[N];
//记录输入的情况，因为输入完成之后需要把根相同的结点进行合并
struct node
{
	int u,v;
	int w;
	node(int u1,int v1,int w1):u(u1),v(v1),w(w1){}
};
//记录图的情况
map<int,vector<int> > mg;
//bfs是否访问过
bool visited[N];
//是否在图中存在回路
bool res;



//查找一个并查集的根，同时进行路径压缩
int find(int u)
{
	int t=u;
	while(t!=pre[t])
	{
		t=pre[t];
	}
	int k=u;
	while(k!=t)
	{
		int i=pre[k];
		pre[k]=t;
		k=i;
	}
	return t;
}

//合并两个结点
void merge(int u,int v)
{
	int fu=find(u);
	int fv=find(v);
	if(fu!=fv)
	{
		pre[fu]=fv;
	}
}

//使用dfs寻找回路
void dfs(int x)
{
	if(res)
	{
		return;
	}
	if(visited[x])
	{
		res=1;
		return;
	}
	visited[x]=1;
	int len=mg[x].size();
	for(int i=0;i<len;i++)
	{
		if(mg.count(mg[x][i]))
			dfs(mg[x][i]);
	}
	
}


int main()
{
	//freopen("a.txt","r",stdin);
	int t,n,l,u,v,w;
	scanf("%d ",&t);
	while(t--)
	{
		//初始化所有结点都为根
		for(int i=1;i<N;i++)
			pre[i]=i;
		//记录输入情况的向量
		vector<node> nv;
		scanf("%d %d ",&n,&l);
		for(int i=0;i<l;i++)
		{
			scanf("%d %d %d",&u,&v,&w);
			node no(u,v,w);
			if(w==0)
			{
				//合并两个结点
				merge(u,v);
			}
			else
			{
				//将输入临时存到向量中
				nv.push_back(no);
			}
		}

		//建立图
		mg.clear();
		int len=nv.size();
		for(int i=0;i<len;i++)
		{
			node tn=nv[i];
			int tu,tv;
			if(tn.w==1)
			{
				tu=find(tn.u);
				tv=find(tn.v);
			}
			else
			{
				tu=find(tn.v);
				tv=find(tn.u);
			}
			if(mg.count(tu))
			{
				bool tf=0;
				for(int j=0;j<mg[tu].size();j++)
				{
					if(mg[tu][j]==tv)
					{
						tf=1;
					}
				}
				if(!tf)
				{
					mg[tu].push_back(tv);
				}
			}
			else
			{
				vector<int> ttv;
				ttv.clear();
				ttv.push_back(tv);
				mg[tu]=ttv;
			}
		}

		res=0;
		for(int i=1;i<=n;i++)
		{
			if(res)
				break;
			if(mg.count(i))
			{
				memset(visited,0,sizeof(visited));
				dfs(i);
			}
		}

		if(!res)
		{
			puts("YES");
		}
		else
		{
			puts("NO");
		}
		
	}
	return 0;
}


