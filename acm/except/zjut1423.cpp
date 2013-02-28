#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 101;
const double EXP = 1e-10;
double a[MAX][MAX], b[MAX], x[MAX];

char maze[11][11];
int seq[10][10];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, m, N;
bool flag;

struct Point
{
    void set(int i, int j)
    {
        x = i;
        y = j;
    }
    int x, y;
};

Point dk, ep, sur[4], ps[MAX];

bool valid(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m || maze[x][y] == 'X')
        return 0;
    return 1;
}

//找到从起点可以到达的点，标识为1
//并记录是第几个点，这样易于构造高斯方程
//用seq来标识它属于第几组方程
void dfs(int i, int j)
{
    if (!valid(i, j) || seq[i][j] != -1)
        return;

    seq[i][j] = N;
    ps[N].set(i, j);
    N++;
    for (int k = 0; k < 4; k++)
        dfs(i + dir[k][0], j + dir[k][1]);
}


//实现高斯消元，都一样，可以记下以后用
void gauss()
{
    flag = 1;

    int k, i, index, j;
    double maxi, d;

    for (k = 0; k < N; k++)    
    {
        maxi = 0;

        for (i = k; i < N; i++)    
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

            for (i = 0; i < N; i++)
            {
                temp = a[index][i];
                a[index][i] = a[k][i];
                a[k][i] = temp;
            }
        }

        for (i = k + 1; i < N; i++)        
        {
            d = a[i][k] / a[k][k];
            b[i] -= b[k] * d;
            a[i][k] = 0;

            for (j = k + 1; j < N; j++)
                a[i][j] -= a[k][j] * d;

        }
    }

    for (i = N - 1; i >= 0; i--)        
    {
        for (j = i + 1; j < N; j++)
        {
            b[i] -= a[i][j] * x[j];
        }

        x[i] = b[i] / a[i][i];
    }
}



int main()
{
    //freopen("a.txt", "r", stdin);
    int i, j, k, c;
    double r;
    while (cin >> n >> m)
    {
        for (i = 0; i < n; i++)
            cin >> maze[i];

        memset(seq, -1, sizeof(seq));

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
            {
                if (maze[i][j] == 'D')
                    dk.set(i, j);
                if (maze[i][j] == 'E')
                    ep.set(i, j);
            }
            N = 0;
            dfs(dk.x, dk.y);
            if (seq[ep.x][ep.y] == -1)
            {
                puts("tragedy!");
                continue;
            }

            memset(a, 0, sizeof(a));
            memset(b, 0, sizeof(b));
            memset(x, 0, sizeof(x));

            //终点的步数为0
            a[seq[ep.x][ep.y]][seq[ep.x][ep.y]] = 1;

            for (i = 0; i < N; i++)
            {
                //对每个可达的点，构造一个方程
                if (ps[i].x != ep.x || ps[i].y != ep.y)
                {    
                    c = 0;
                    for (k = 0; k < 4; k++)
                    {
                        if (valid(ps[i].x + dir[k][0], ps[i].y + dir[k][1]))
                        {
                            sur[c].set(ps[i].x + dir[k][0], ps[i].y + dir[k][1]);
                            c++;
                        }
                    }
                    a[i][i] = 12;
                    b[i] = 12;
                    for (k = 0; k < c; k++)
                    {
                        a[i][seq[sur[k].x][sur[k].y]] = -12 / c;
                    }
                }


            }

            //高斯消元，得到结果
            gauss();

            //实际要求的结果
            r = x[seq[dk.x][dk.y]];

            //超过1000000步或无解，则无法完成任务
            if (!flag || r > 1000000)
            {
                puts("tragedy!");
            }

            else
            {
                printf("%.2lf\n", r);
            }


    }

    return 0;
}
