#include<iostream>
using namespace std;
const int N=32;
int ans[N];
//因为排名可能超过int型，所以用__int64
//为了运算的时候不出现错误，所以把n和l的类型也设置成__int64
__int64 n,l,k;

//计算组合数
__int64 c(__int64 w,__int64 m)
{
    if(w>m)
    {
        return 0;
    }
    __int64 res=1;
    for(int i=1;i<=w;i++)
    {
        //注意整数的除可能会出错，如果顺序不一样的话
        res=res*(m-i+1)/(i);
    }
    return res;
}
//cnt为最多能有几个1，rank表示需要排到多少名，把全0的情况忽略
//每次找最高位的1
void cal(__int64 cnt, __int64 rank)
{
    if(rank>0)
    {
        __int64 pre,cur=0;
        int i;
        //i表示剩余的位数，而且正好可以作为ans的下标，因为ans的下标是从0开始的，结束的时候第i位为1
        for(i=0;;i++)
        {
            pre=cur;
            //最高位已经用掉了一个1，所以剩下的最多还能用cnt-1个1
            for(int j=0;j<=i&&j<cnt;j++)
            {
                cur+=c(j,i);
                //printf("c(%d,%d)=%d\n",j,i,c(j,i));
                if(cur>=rank)
                {
                    goto end;
                }
            }
        }
end:;
        //因为10000的情况也占用一个排名，所以pre+1
        rank-=(pre+1);
        //下标从0开始，所以实际为1的位置为i-1
        ans[i]=1;
        cal(cnt-1,rank);

    }

}




int main()
{
    //freopen("a.txt","r",stdin);
    int t;
    scanf("%d ",&t);
    while(t--)
    {
        scanf("%I64d %I64d %I64d ",&n,&l,&k);
        memset(ans,0,sizeof(ans));
        //不把全0的情况考虑在内
        k--;
        cal(l,k);
        for(__int64 i=n-1;i>=0;i--)
        {
            printf("%d",ans[i]);
        }
        puts("");
    }

    return 0;
}
