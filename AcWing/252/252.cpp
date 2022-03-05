#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N * 2;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int p[N], q[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int get_size(int u, int fa)
{
    if(st[u]) return 0;
    int res = 1;
    for(int i = h[u]; ~i; i = ne[i])
        if(e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

int get_wc(int u, int fa, int tot, int &wc)
{
    if(st[u]) return 0;
    int sum = 1, ms = 0;
    for(int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if(ms <= tot / 2) wc = u;
    return sum;
}

void get_dist(int u, int fa, int dist, int &qt)
{
    if(st[u]) return;
    q[qt++] = dist;
    for(int i = h[u]; ~i; i = ne[i])
        if(e[i] != fa)
            get_dist(e[i], u, dist + w[i], qt);
}

int get(int a[], int k)
{
    sort(a, a + k);
    int res = 0;
    for(int i = k - 1, j = -1; i >= 0; i--)
    {
        while(j + 1 < i && a[j + 1] + a[i] <= m) j++;
        j = min(j, i - 1);
        res += j + 1;
    }
    return res;
}

int calc(int u)
{
    if(st[u]) return 0;
    int res = 0;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;

    int pt = 0;
    for(int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i], qt = 0;
        get_dist(j, -1, w[i], qt);
        res -= get(q, qt);
        for(int k = 0; k < qt; k++)
        {
            if(q[k] <= m) res++;
            p[pt++] = q[k];
        }
    }
    res += get(p, pt);

    for(int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);
    return res;
}

int main()
{
    while(scanf("%d%d", &n, &m), n || m)
    {
        memset(st, 0, sizeof st);
        memset(h, -1, sizeof h);
        idx = 0;
        for(int i = 0; i < n - 1; i++)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
        printf("%d\n", calc(0));
    }
    return 0;
}
