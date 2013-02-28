#include<iostream>
using namespace std;

const int N=10007;
const int M=100005;
char s[M];
int next[M],e[M],n,sum[M];
void kmpNext()
{
    int i=0,j=-1;
    next[0]=-1;
    while(i<n)
    {
        while(j>=0&&s[i]!=s[j])
            j=next[j];
        i++,j++;
        if(s[i]==s[j]) next[i]=next[j];
        else next[i]=j;
    }
}
int main()
{
    freopen("a.txt", "r", stdin);
    while(scanf("%s",s)!=EOF)
    {
        n=strlen(s);
        kmpNext();
        int i;
        e[0]=sum[0]=2;
        for(i=1;i<n;i++)
        {
            e[i]=2;
            if(i-2>=next[i])
            {
                if(next[i]>=0)
                    e[i]+=sum[i-1]-sum[next[i]]+N;
                else e[i]+=sum[i-1];
            }
            e[i]%=N;
            sum[i]=(sum[i-1]+e[i])%N;
        }
        printf("%d\n",sum[n-1]);
    }
}
