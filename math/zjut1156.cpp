#include<iostream>
using namespace std;
const int N=10;
//a数组只是用来比较大小
__int64 a[N]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
//b[i]=zero(1,a[i]),[1,a[i]]之间0的个数
__int64 b[N]={0,1,11,192,2893,38894,488895,5888896,68888897,788888898};
//c[i]=zero(a[i]+1,a[i]*2)(i>0)(c[0]=zero(1,2))[(n-1)*a[i]+1,n*a[i]]之间0的个数
__int64 c[N]={0,1,20,300,4000,50000,600000,7000000,80000000,900000000};

int bitNum(__int64 x)
{
    int c=0;
    while(x)
    {
        x/=10;
        c++;
    }
    return c;
}

//计算[0,x]之间的0的个数
__int64 solve(__int64 x)
{
    if(x<0)
    {
        return 0;
    }
    if(x<10&&x>=0)
    {
        return 1;
    }
    int i,j;
    __int64 sum,k;
    for(i=N-1;i>=0;i--)
    {
        //寻找第一个比x小的a[i]
        //然后可以计算zero(1,a[i])以及zero(n*a[i]+1,(n+1)*a[i])，(n+1)*a[i]<=x且n>0
        //最后剩下的工作是计算[x/a[i]*a[i]+1,x]之间0的个数，这个地方是最难的
        //100001~189000，这是不能只计算1~89000中0的个数，因为00001也包含了4个0
        //1~9要多加4个0,10~99这90个数要多加3个0，而100~999这900个数要多加2个0，以此类推
        if(x>=a[i])
        {
            break;
        }
    }
    //zero(1,a[i])
    sum=b[i];
    //zero(n*a[i]+1,(n+1)*a[i])，(n+1)*a[i]<=x且n>0
    sum+=(x/a[i]-1)*c[i];
    //减去最高位后余下的数为k
    k=x-(x/a[i])*a[i];
    //计算额外的0
    int ex=bitNum(x)-2;
    if(ex!=0)
    {
        for(j=1;j<N;j++)
        {
            //如果k>=10^j的情况
            //比如100001，则从1-9每个数都要加上4个0，即4*9
            //再有100010-100099，90*3
            if(k>=a[j])
            {
                sum+=(ex-j+1)*(a[j]-a[j]/10);
            }
            else
            {
                break;
            }
        }
        //这里还有些问题？
        sum+=(k-a[j-1]+1)*(ex-j+1);
    }
    

    return sum+solve(k);

}

int main()
{
    //freopen("a.txt","r",stdin);
    __int64 m,n;
    while(cin>>m>>n)
    {
        if(m==-1&&n==-1)
        {
            break;
        }
        cout<<solve(n)-solve(m-1)<<endl;
    }
    return 0;
}
