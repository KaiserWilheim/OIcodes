#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int m, n, k, l, d;
int x[N], y[N]; 
int c[N], o[N];
int main()
{
    scanf("%d%d%d%d%d", &m, &n, &k, &l, &d);
    for(int i = 1; i <= d; i++)
    {
        int xi, yi, pi, qi;
        scanf("%d%d%d%d", &xi, &yi, &pi, &qi);
        if(xi == pi)
            x[min(yi, qi)]++;
        else
            y[min(xi, pi)]++;
    }
    for(int i = 1; i <= k; i++)
    {
        int maxn = -1;
        int p;
        for(int j = 1; j < m; j++)
        {
            if(y[j] > maxn)
            {
                maxn = y[j];
                p = j;
            }
        }
        y[p] = 0;
        c[p]++;
    }
    for(int i = 1; i <= l; i++)
    {
        int maxn = -1;
        int p;
        for(int j = 1; j < n; j++)
        {
            if(x[j] > maxn)
            {
                maxn = x[j];
                p = j;
            }
        }
        x[p] = 0;
        o[p]++;
    }
    for(int i = 0; i < 1005; i++)
    {
        if(c[i])
            printf("%d ", i);
    }
    printf("\n");
    for(int i = 0; i < 1005; i++)
    {
        if(o[i])
            printf("%d ", i);
    }
    return 0;
}
