#include <stdio.h>
#include <memory.h>
const int N=50005;
int s[N];
struct node
{
    int a,b,c;
};
node ns[N];

int main()
{
    //freopen("a.txt","r",stdin);
    int n;
    while(scanf("%d ",&n)!=EOF)
    {
        int maxv=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d %d %d ",&ns[i].a,&ns[i].b,&ns[i].c);
            ns[i].b++;
            if(ns[i].b>maxv)
            {
                maxv=ns[i].b;
            }
        }
        //memset的一种方法
        memset(s,0,(maxv+1)<<2);
        bool flag=1;
        //while循环这段是重点
        while(flag)
        {
            flag=0;
            for(int i=0;i<n;i++)
            {
                if(s[ns[i].b]<s[ns[i].a]+ns[i].c)
                {
                    s[ns[i].b]=s[ns[i].a]+ns[i].c;
                    flag=1;
                }    
            }
            //从大到小遍历
            for(int i=maxv;i;i--)
            {
                if(s[i]>s[i-1]+1)
                {
                    s[i-1]=s[i]-1;
                }
            }
            //从小到大遍历
            for(int i=1;i<=maxv;i++)
            {
                if(s[i]<s[i-1])
                {
                    s[i]=s[i-1];
                }
            }

        }

        printf("%d\n",s[maxv]);
    }
    return 0;
}
