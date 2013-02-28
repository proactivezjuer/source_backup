//线段树面积
#include <cstdio>
#include <algorithm>
#include <vector>

const int MAX_N = 2001;
const double EXP = 0.00001;
double hash[2*MAX_N];

struct YEdge
{
    double y1, y2;
    double x;
    bool flag;
};
YEdge edges[MAX_N];

struct Node
{
    int start, end;
    int cnt;
    double measure;
};
Node nodes[3*MAX_N];
double xArray[2*MAX_N];
double yArray[2*MAX_N];

double myabs(double a)
{
    return a > 0 ? a : 0-a;
}

bool equals(double a, double b)
{
    if (myabs(a-b) < EXP)
    {
        return true;
    }
    return false;
}

int cmp(const void *a, const void *b)
{
    double c = *(double *)a;
    double d = *(double *)b;
    if (equals(c,d))
        return 0;
    if (c - d > 0)
        return 1;
    else
        return -1;
}

int cmp1(const void *a, const void *b)
{
    YEdge e1 = *(YEdge *)a;
    YEdge e2 = *(YEdge *)b;
    if (equals(e1.x, e2.x))
    {
        return 0;
    }

    if (e1.x - e2.x > 0)
        return 1;
    else
        return -1;

}

void build_tree(int start, int end, int pos)
{
    nodes[pos].cnt = 0;
    nodes[pos].measure = 0;
    nodes[pos].start = start;
    nodes[pos].end = end;
    if (end-start > 1)
    {
        int mid = (start + end) >> 1;
        build_tree(start, mid, pos << 1);
        build_tree(mid, end, pos << 1 | 1);
    }
}

void update_tree(int pos)
{
    if (nodes[pos].end - nodes[pos].start == 1 && nodes[pos].cnt < 2)
    {
        nodes[pos].measure = 0;
    }
    else if (nodes[pos].cnt >= 2)
    {
        nodes[pos].measure = hash[nodes[pos].end] - hash[nodes[pos].start];
    }
    else
    {
        nodes[pos].measure = nodes[pos<<1].measure + nodes[pos<<1|1].measure;    
    }
}



void insert_tree(double y1, double y2, int pos)
{

    int mid = (nodes[pos].start + nodes[pos].end) >> 1;
    if (nodes[pos].end - nodes[pos].start == 1)
    {
        nodes[pos].cnt++;
        update_tree(pos);
        return;
    }
    if (equals(hash[nodes[pos].start], y1)&&equals(hash[nodes[pos].end], y2))
    {
        nodes[pos].cnt++;
        insert_tree(y1, hash[mid], pos << 1);
        insert_tree(hash[mid], y2, pos << 1 | 1);
    }
    else
    {
        if (equals(hash[mid], y2) || y2 < hash[mid]) 
        {
            insert_tree(y1, y2, pos << 1);
        }
        else if (equals(hash[mid], y1) || y1 > hash[mid]) 
        {
            insert_tree(y1, y2, pos << 1 | 1);
        }
        else
        {
            insert_tree(y1, hash[mid], pos << 1);
            insert_tree(hash[mid],y2, pos << 1 | 1);
        }
    }
    update_tree(pos);    

}

void delete_tree(double y1, double y2, int pos)
{
    int mid = (nodes[pos].start + nodes[pos].end) >> 1;
    if (nodes[pos].end - nodes[pos].start == 1)
    {
        nodes[pos].cnt--;
        update_tree(pos);
        return;
    }
    if (nodes[pos].cnt > 0)
        nodes[pos].cnt--;
    if (equals(hash[mid], y2) || y2 < hash[mid]) 
    {
        delete_tree(y1, y2, pos << 1);
    }
    else if (equals(hash[mid], y1) || y1 > hash[mid]) 
    {
        delete_tree(y1, y2, pos << 1 | 1);
    }
    else
    {
        delete_tree(y1, hash[mid], pos << 1);
        delete_tree(hash[mid],y2, pos << 1 | 1);
    }
    
    update_tree(pos);    

}



int main()
{
    int t, n;
    double ldx, ldy, rux, ruy;
    freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        int i;
        for (i = 0; i < 2*n; i += 2)
        {
            scanf("%lf %lf %lf %lf", &ldx, &ldy, &rux, &ruy);
            edges[i].y1 = ldy;
            edges[i].y2 = ruy;
            edges[i].x = ldx;
            edges[i].flag = true;
            edges[i+1].y1 = ldy;
            edges[i+1].y2 = ruy;
            edges[i+1].x = rux;
            edges[i+1].flag = false;
            xArray[i] = ldx;
            xArray[i+1] = rux;
            yArray[i] = ldy;
            yArray[i+1] = ruy;
        }
        qsort(edges, i, sizeof(YEdge), cmp1);
        qsort(xArray, i, sizeof(double), cmp);
        qsort(yArray, i, sizeof(double), cmp);
        int k = 0;
        hash[0] = yArray[0];
        for (i = 1; i < 2*n; i++)
        {
            if (!equals(yArray[i], yArray[i-1]))
            {
                k++;
                hash[k] = yArray[i];
            }
        }

        build_tree(0, k, 1);
        double sum = 0;
        for (i = 0; i < 2*n-1; i++)
        {
            if (edges[i].flag)
            {
                insert_tree(edges[i].y1, edges[i].y2, 1);
            }
            else
            {
                delete_tree(edges[i].y1, edges[i].y2, 1);
            }
            sum += nodes[1].measure * (xArray[i+1] - xArray[i]);
        }

        printf("%.2lf\n", sum);
    }
    return 0;
}

