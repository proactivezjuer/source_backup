/*AC代码*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge    //构造边的结构，可以edges的向量中，对其进行排序
{
    int from, to;
    Edge(int f, int t): from(f), to(t){}
};

int pre[1001], a[1001][1001];

int find(int x)
{
    int r;
    r = x;
    while (pre[r] != -1)
    {
        r = pre[r];
    }

    int i = x;
    while (i != r)
    {
        x = i;
        i = pre[i];
        pre[x] = r;
    }

    return r;
}

void join(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
    {
        pre[fx] = fy;
    }
}

bool cmp(const Edge &e1, const Edge &e2)    //排序的比较函数
{
    return a[e1.from][e1.to] < a[e2.from][e2.to];
}

int main()
{
    int i, j, q, n, tw, k;
    vector<Edge> edges;
    while (cin >> n)
    {
        tw = 0;
        edges.clear();
        memset(pre, -1, sizeof(pre));
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)    //输入图
            {
                cin >> a[i][j];
            }
        for (i = 1; i < n; i++)
            for (j = i + 1; j <= n;j++)    
            {
                edges.push_back(Edge(i, j));    //把边加入容器edges中
            }
        cin >> q;
        for (k = 0; k < q; k++)
        {
            cin >> i >> j;    //已经存在的边
            join(i, j);        
        }

        sort(edges.begin(), edges.end(), cmp);    //把边按从小到大排序

        for (i = 0; i < edges.size(); i++)
        {
            if (find(edges[i].from) != find(edges[i].to))    //把两个还没相连的最小边相连
            {
                join(edges[i].from, edges[i].to);
                tw += a[edges[i].from][edges[i].to];    //算花费
            }
        }
        cout << tw << endl;
    }

    return 0;
}





