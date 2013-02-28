#include <stdio.h>
#include <memory.h>
#include <queue>
using namespace std;
const int ODD=8;
const int EVEN=4;
const int R=55;
const int C=55;
int odir[ODD][2]={{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
int edir[EVEN][2]={{-2,0},{0,2},{2,0},{0,-2}};
int row,col;
bool odd[R][C],even[R][C];

bool validate(int x,int y)
{
    return x>=1&&x<=row&&y>=1&&y<=col;
}
struct Point
{
    int x,y;
    int c;
};
Point p1,p2;
int bfs()
{    
    if(p1.x==p2.x&&p1.y==p2.y)
    {
        return 0;
    }
    queue<Point> q;
    p1.c=0;
    q.push(p1);
    even[p1.x][p1.y]=1;
    while(!q.empty())
    {
        Point front=q.front();
        q.pop();
        int c=front.c;
        c++;
        int x=front.x;
        int y=front.y;
        if(c&1)
        {
            for(int i=0;i<ODD;i++)
            {
                if(validate(x+odir[i][0],y+odir[i][1])&&!odd[x+odir[i][0]][y+odir[i][1]])
                {
                    if(x+odir[i][0]==p2.x&&y+odir[i][1]==p2.y)
                    {
                        return c;
                    }
                    Point temp;
                    temp.c=c;
                    temp.x=x+odir[i][0];
                    temp.y=y+odir[i][1];
                    odd[x+odir[i][0]][y+odir[i][1]]=1;
                    q.push(temp);
                }
            }
        }
        else
        {
            for(int i=0;i<EVEN;i++)
            {
                if(validate(x+edir[i][0],y+edir[i][1])&&!even[x+edir[i][0]][y+edir[i][1]])
                {
                    if(x+edir[i][0]==p2.x&&y+edir[i][1]==p2.y)
                    {
                        return c;
                    }
                    Point temp;
                    temp.c=c;
                    temp.x=x+edir[i][0];
                    temp.y=y+edir[i][1];
                    even[x+edir[i][0]][y+edir[i][1]]=1;
                    q.push(temp);
                }
            }
        }
    }
    return 0;
    
}

int main()
{
    //freopen("a.txt","r",stdin);
    while(scanf("%d %d ",&row,&col)!=EOF)
    {
        scanf("%d %d %d %d ",&p1.x,&p1.y,&p2.x,&p2.y);
        memset(odd,0,sizeof(odd));
        memset(even,0,sizeof(even));
        int step=bfs();
        printf("%d\n",step);
    }
    return 0;
}
