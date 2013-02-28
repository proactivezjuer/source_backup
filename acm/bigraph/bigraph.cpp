#include <stdio.h>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;
const int N=1505;
int n;    //输入的结点的个数
vector<int> g[N];    //图的表示
int mm;    //最大匹配的个数
int visited[N];    //每一次宽度优先遍历之前初始化，然后标志已经访问过的点
int pl[N];    //previous left node前一个左点，这是局部的
int lmr[N];    //左侧匹配的右侧点，这是全局的
int rml[N];    //右侧匹配的左侧点，这是全局的
//pl,lmr,rml是用来标识寻找到的增广路径，以及进行取反时用到,用-1表示没有匹配的
//这里增广路径是从左侧出发，如果能够找到增广路径，增广路径的最后一条边必定是不在原匹配中的，而且一个逻辑上的方向是左侧到达右侧的，即右侧的点是最后结束的点
//pl可以用来真正标识路径

void reverse(int l, int r)
{
    while(l!=-1)
    {
        int nl = pl[l];
        int nr = lmr[l];
        lmr[l] = r;
        rml[r] = l;
        //这里为什么不做rml[nr]，首先不知道nr是不是-1，其次如果nr不是-1，下次遍历肯定可以修改，一次只修改一个r和一个l，不要太aggressive
        l = nl;
        r = nr;
    }
    mm++;    //寻找到一条增广路径，原来的最大匹配数就加1

}

void findAugment(int s)    //寻找从s左点出发的一条增广路径
{
    bool found = 0;    //判断是否寻找到一条增广路径，因为有二重循环，便于跳出
    memset(pl,-1,sizeof(pl));
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    while(!q.empty()&&!found)
    {
        int f = q.front();
        q.pop();
        visited[s] = 1;
        for(int i=0; i<g[f].size(); i++)
        {
            int j = g[f][i];
            if(!visited[j])
            {
                visited[j]=1;
                if(rml[j]==-1)  //如果不能从右点再次出发，那么就找到了一条增广路径
                {
                    found=1;
                    reverse(f,j);
                    break;
                }
                else
                {
                    int k = rml[j];
                    pl[k] = f;
                    q.push(k);
                }
            }

        }
    }
}

void maxMatch()
{
    mm = 0;
    memset(lmr,-1,sizeof(lmr));
    memset(rml,-1,sizeof(rml));
    //左边匹配右边和右边匹配左边都算了一下，所以计算出来的匹配的个数需要除2，对每个点都寻找增广路径
    for(int i=0; i<n; i++)
    {
        findAugment(i);
    }
}


int main ( int argc, char *argv[] )
{

//    freopen("data", "r", stdin);
    while(scanf("%d ", &n)!=EOF)
    {
        for(int i=0; i<n; i++)
        {
            g[i].clear();
        }
        int u,v,m;
        for(int i=0; i<n; i++)
        {
            scanf("%d:(%d) ", &u, &m);
            for(int j=0; j<m; j++)
            {
                scanf("%d ", &v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
        maxMatch();
        printf("%d\n", mm/2);
    }
    return 0;
}
