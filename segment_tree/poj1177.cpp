//线段树周长
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_N = 10001;

int hash[2*MAX_N],str2[2*MAX_N], hash2[2*MAX_N];
//numcover[x]表示以x结点为根的线段树中互不相交的线段的个数（使用numcover的用处？）
//leftcover表示一棵树的最左节点是否被覆盖，rightcover表示一棵树的最右结点是否被覆盖
//使用leftcover和rightcover的目的是为了计算numcover，因为如果右子树的最左结点和左子树的左右结点都被覆盖了
//那么它们就可以连成一条线段了，计算numcover的时候线段树就需要减1
int len[2*MAX_N],leftcover[2*MAX_N],rightcover[2*MAX_N],numcover[2*MAX_N];
//使用数组模拟线段树
/*
len[i]表示第i个结点长度：根据自身或子结点的覆盖情况来的
leftcover[i]表示第i个结点的左子树是否有被覆盖，这个左子树是指以i这个结点为根的线段树的最左的叶子是否被覆盖了
rightcover[i]同leftcover[i]相似
numcover[i]是指这个结点（这条线段）被覆盖的次数
hash[i]从坐标映射到下标（但是负的不是有问题吗？），hash2[i]是从下标映射到坐标（都是y方向的）
str映射的是纵向边的情况，同时记录了x的情况（x有相同的也不会出现问题的，因为这样横向边加的是0）
str2映射的是包含重复点的y的情况
*/

//表示一条线段
struct In
{
    int start;//开始坐标，如y1
    int end;//结束坐标，如y2，y1y2形成了沿y轴的纵向边
    int pos;//位置，即线段所在的x轴的位置
    bool flag;//是否为入边
}str[2*MAX_N];

//线段树的一个结点
struct Node
{
    int l;//起始位置对应的下标
    int r;//结束位置对应的下标
    int mid; //这个只是为了简化，实际上没用处  
    int sum; 
}node[3*MAX_N];

//创建线段树，起始下标为l，结束下标为r，当前结点[l,r]所插入的位置为num，所谓的位置是指数组的下标
//使用数组来模拟线段树的
void B_Tree( int l , int r , int num){
    node[num].l = l;
    node[num].r = r;
    node[num].mid = (l+r)>>1;
    node[num].sum = 0;
    //判断是否为叶子结点
    if( l+1 != r ){
        B_Tree( l , node[num].mid , num<<1 );
        B_Tree( node[num].mid , r , num<<1|1 );    
    }
}

//更新线段树，线段树的内容是要实时更新的
//比如插入一条线段，删除一条线段都是要更新的
//这里的r和l压根没用，直接根据node[num]得到node[num].l和node[num].r更好
void Updata( int l , int r , int num ){
    if( node[num].sum > 0 ){   //当它已被覆盖时，无论被覆盖了几遍，长度都是区间的长度
        len[num] = hash2[ node[num].r ] - hash2[ node[num].l ];  //并集区间的长度,hash2把坐标重新映射成了值
        leftcover[num] = rightcover[num] = 1;    //表示左区间和右区间都被覆盖 
        numcover[num] = 1;    //并集的独立区间数目
    }else if( r > l+1 ){               //内结点
        //长度为左右区间之和
        len[num] = len[num<<1]+len[num<<1|1];
        leftcover[num] = leftcover[num<<1];
        rightcover[num] = rightcover[num<<1|1];
        numcover[num] = numcover[num<<1]+numcover[num<<1|1] - leftcover[num<<1|1]*rightcover[num<<1];
    }else{                            //叶结点
        len[num] = 0;
        leftcover[num] = rightcover[num] = 0;
        numcover[num] = 0;
    }
}

//往根结点为node[num]的线段树中插入[l,r]这条线段，l,r都是下标
void Insert( int l , int r , int num ){
    if( node[num].l == l && r == node[num].r ){
        node[num].sum++; 
    }else{
        //插入的线段的右坐标，即r都比mid小，所以插入到左子树，左子树的坐标为num<<1
        if( node[num].mid >= r ){
            Insert( l , r , num<<1 );    
        }else if( node[num].mid <= l ){
            Insert( l , r , num<<1|1 );      
        }else{
            Insert( l , node[num].mid , num<<1 );
            Insert( node[num].mid , r , num<<1|1 ); 
        }
    }  
    
    Updata( node[num].l , node[num].r , num );

}
//删除
void Delete( int l , int r , int num ){
    if( node[num].l == l && r == node[num].r ){
        node[num].sum--; 
    }else{
        if( node[num].mid >= r ){
            Delete( l , r , num<<1 );    
        }else if( node[num].mid <= l ){
            Delete( l , r , num<<1|1 );      
        }else{
            Delete( l , node[num].mid , num<<1 );
            Delete( node[num].mid , r , num<<1|1 );     
        }
    }
    Updata( node[num].l , node[num].r , num );
    
}

//如果有两个完全
int cmp( const void *a , const void *b ){
    
    struct In *c = ( In *)a;
    struct In *d = ( In *)b;
    if (c->pos == d->pos && c->start == d->start && c->end == d->end && !c->flag && d->flag)
        return 1;
    return c->pos - d->pos;    
} 

int intcmp( const void *a , const void *b ){
    return *( int *)a - *(int *)b;    
}

int main()
{   
    //freopen("in.txt", "r", stdin);
    int i , j , x1 , x2 , y1 , y2 ,cas, k = 0;
    scanf("%d",&cas);
    while( cas-- ){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        //弄个str2只是把输入的全部y值做一下排序，然后检查是否存在相同的y值，如果存在就将其去除
        str[k].start = y1 , str[k].end = y2 , str[k].flag = true , str[k].pos = x1 , str2[k] = y1;
        k++;
        str[k].start = y1 , str[k].end = y2 , str[k].flag = false , str[k].pos = x2 , str2[k]= y2;
        k++;
    }
    qsort( str , k , sizeof(In) , cmp );
    qsort( str2 , k , sizeof(int) , intcmp );
    int l = 1;
    //hash是值到下标，hash2是下标到值
    hash[str2[0]] = l;
    hash2[1] = str2[0];
    for( i = 1 ; i < k ; i++ ){
        if( str2[i] != str2[i-1] ){
            l++;
            hash[str2[i]] = l;    
            hash2[l] = str2[i];
        } 
    }
    B_Tree( 1 , l , 1 );
    int sum = 0 , ans = 0 , value = 0;
    //排序的时候需要注意两条完全重合的边，且一条为输入边，一条为输出边，这时输入边要放在前面，这样才不会出现错误
    for( i = 0 ; i < k-1 ; i++ ){
        if( str[i].flag ){
            Insert( hash[str[i].start] , hash[str[i].end] , 1 );    
        }else{
            Delete( hash[str[i].start] , hash[str[i].end] , 1 );       
        }
        //增加横向边的长度，即平行于x轴的线段的长度
        ans += 2*( str[i+1].pos - str[i].pos )*numcover[1];
        //增加纵向边的长度，即平行于y轴的线段的长度
        ans += abs( len[1] - value );
        value = len[1];
    }
    Delete( hash[str[i].start] , hash[str[i].end] , 1 );
    ans += abs( len[1] - value );
    printf("%d\n",ans);
    return 0;    
}

