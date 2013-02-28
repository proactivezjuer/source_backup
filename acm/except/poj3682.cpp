#include <iostream>
using namespace std;
int k;
double p;
const int MAX = 1001;
double e[MAX], f[MAX];

int main()
{
    //freopen("a.txt", "r", stdin);
    while (scanf("%d ", &k) != EOF && k)
    {
        scanf("%lf ", &p);
        e[k] = 0;
        f[k] = 0;
        for (int i = k-1; i >= 0; i--)
        {
            e[i] = e[i+1] + 1/p;
        }
        for (int i = k-1; i >= 0; i--)
        {
            f[i] = 2*(1-p)/p * e[i] + f[i+1] + 2 * e[i+1] + 1/p;
        }
        printf("%.3lf %.3lf\n", e[0], f[0]);
    }
    return 0;
}
