/*
使用优先队列速度会快很多
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 1001;
const int Inf = 1001;

int a[MAX][MAX];
int n, m;
int d[MAX];
bool visited[MAX];
//bool cmp(int u, int v)
//{
//    return d[u] < d[v];
//}
struct cmp
{
    bool operator()(int u, int v)
    {
        return d[u] > d[v];
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
    int k, u, v, w;
    scanf("%d", &k);
    //deque<int> order;


    while (k--)
    {
        //order .clear();
        scanf("%d%d", &n, &m);
        //memset(d, Inf, (n+1)*sizeof(int));
        //memset(visited, false, (n+1)*sizeof(bool));
        int i, j;
        for (i = 1; i <= n; i++)
            d[i] = Inf;
        for (i = 1; i <= n; i++)
            visited[i] = false;
        for (i = 1; i <= n; i++)
        {
            //memset(a[i], Inf, (n+1)*sizeof(int));
            for (j = 1; j <= n; j++)
                a[i][j] = Inf;
        }
        for (i = 0; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            a[u][v] = w;
            a[v][u] = w;
        }

        priority_queue<int, vector<int>, cmp> pq;
        for (i = 2; i <= n; i++)
        {
            if (a[1][i] != Inf)
            {
                d[i] = a[1][i];
                pq.push(i);
            }
            //order.push_back(i);

        }
        //sort(order.begin(), order.end(), cmp);
        while(!pq.empty() && !visited[n])
        {
            //int i = order.front();
            //order.pop_front();
            int i = pq.top();
            //cout << d[i] << endl;
            pq.pop();
            if (visited[i] == true)
                continue;
            visited[i] = true;
            for (int j = 2; j <= n; j++)
            {
                if(!visited[j] && d[i] + a[i][j] < d[j])
                {
                    d[j] = d[i] + a[i][j];
                    pq.push(j);

                }
            }
            //sort(order.begin(), order.end(), cmp);
        }
        if (d[n] != Inf)
        {
            cout << d[n] << endl;
        }
        else
        {
            cout << -1 << endl;
        }


    }

    return 0;
}

