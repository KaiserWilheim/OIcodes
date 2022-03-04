#include <bits/stdc++.h>
using namespace std;
const int N = 10010, INF = 1e9;
int f[N], far[N], a[N], flag[N], p, s, t, n;
int main()
{
    scanf("%d", &p);
    scanf("%d%d%d", &s, &t, &n);
    if(s == t)
    {
        int cont = 0, qaq;
        for(int i = 1; i <= n; ++i)
            scanf("%d", &qaq), cont += ((qaq % s) == 0);
        printf("%d\n", cont); 
        return 0;
    }
    for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    a[0] = 0;
    f[0] = 0;
    far[n + 1] = min(p - a[n], 100); 
    p = 0;
    for(int i = 1; i <= n; i++)
    {
        far[i] = min(a[i] - a[i - 1], 90);
        p += far[i];
        flag[p] = 1;
    }
    p += far[n + 1];
    for(int i = 1; i <= p + 9; i++)
    {
        f[i] = INF - 1;
        for(int j = s; j <= t; j++)
            if(i >= j)
                f[i] = min(f[i], f[i - j] + flag[i]);
    }
    int minn = INF - 1;
    for(int i = p; i <= p + 9; i++)
        minn = min(minn, f[i]);
    printf("%d", minn);
}
