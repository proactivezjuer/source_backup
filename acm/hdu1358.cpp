#include <stdio.h>
#include <string.h>

const int N = 1000005;
char str[N];
int pre[N];

int main()
{
    //freopen("in.txt", "r", stdin);
    int cnt = 1;
    int n;    
    while (scanf("%d", &n) != EOF && n)
    {
        scanf("%s", str);
        int j = -1;    
        pre[0] = -1;
        for (int i = 1; i < n; i++)
        {
            while (j > -1 && str[i] != str[j+1])
            {
                j = pre[j];
            }
            if (str[i] == str[j+1])
            {
                j++;
            }
            pre[i] = j;
        }
        printf("Test case #%d\n", cnt);

        for (int i = 2; i <= n; i++)
        {
            
            if (i/(i-1-pre[i-1]) != 1 && i%(i-1-pre[i-1]) == 0)
            {
                printf("%d %d\n", i, i/(i-1-pre[i-1]));
            }
        }
        printf("\n");
        cnt++;
        
    }
    return 0;
}
