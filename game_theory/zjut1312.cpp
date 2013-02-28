#include <stdio.h>
#include <memory.h>
int g[101];
int s[1001];
int b[21];
bool flag[101];
int m, n;
int maxn;

void fun()
{
    memset(g, 0, sizeof(g));
    for(int i = 1; i <= maxn; i++)
    {
        memset(flag, 0, sizeof(flag));
        for (int j = 0; j < n; j++)
        {
            if (i-b[j]>=0)
            {
                flag[g[i-b[j]]] = 1;
            }
        }
        for (int j = 0; ;j++)
        {
            if (!flag[j])
            {
                g[i] = j;
                break;
            }

        }
        
    }
}

int main()
{
    //freopen("a.txt", "r",stdin);
    
    while (scanf("%d ", &m) != EOF)
    {
        maxn = 0;
        for (int i = 0; i < m; i++)
        {
            scanf("%d ", &s[i]);
            if (s[i] > maxn)
                maxn = s[i];
        }
        scanf("%d ", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d ", &b[i]);
        }
        fun();
        int res = 0;
        for (int i = 0; i < m; i++)
        {
            res ^= g[s[i]];
        }
        if (res)
        {
            puts("lily");
        }
        else
        {
            puts("sasnzy");
        }


    }
    return 0;
}
