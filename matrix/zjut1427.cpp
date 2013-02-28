#include<iostream>
using namespace std;
#define MX 2
#define MOD 20090329
__int64 mat[MX][MX]={0,-1,1,3};
//矩阵a乘矩阵b，结果保存在矩阵res
void mult(__int64 a[MX][MX],__int64 b[MX][MX],__int64 res[MX][MX])
{
    int i,j,k;
    for(i=0;i<MX;i++)
    {        
        for(j=0;j<MX;j++)
        {
            res[ i ][ j ]=0;
            for(k=0;k<MX;k++)
                res[ i ][ j ]=(res[ i ][ j ]+a[ i ][ k ]*b[ k ][ j ]+MOD)%MOD;
        }
    }        
}
//矩阵a的p次幂，结果保存在矩阵res，用二分来加速
//如果p是奇数，res=pw(a,p/2)*pw(a,p/2)*a
//如果p是偶数，res=pw(a,p/2)*pw(a,p/2)
void pw(__int64 a[MX][MX],int p,__int64 res[MX][MX])
{
    int i,j;
    if(p==1)
    {
        for(i=0;i<MX;i++)
            for(j=0;j<MX;j++)
                res[ i ][ j ]=a[ i ][ j ];
        return;
    }
    __int64 t1[MX][MX],t2[MX][MX];
    if(p&1)
    {
        pw(a,p/2,t1);
        mult(t1,t1,t2);
        mult(t2,a,res);
    }
    else
    {
        pw(a,p/2,t1);
        mult(t1,t1,res);
    }
}
int main()
{
    freopen("a.txt","r",stdin);
    int n;
    __int64 a[MX][MX]={0,1,0,0},res[MX][MX],t[MX][MX];
    while(scanf("%I64d",&n)&&n)
    {
        if(n==1)
            printf("1\n");
        else
        {
            pw(mat,n,t);
            mult(a,t,res);
            printf("%I64d\n",res[0][0]);
        }
    }
    return 0;
}
