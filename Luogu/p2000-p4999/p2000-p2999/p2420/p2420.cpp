#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, k = 0, h[N], dis[N];
bool vis[N];
struct node
{
    int to, next, w;
}e[N * 2];
void add(int u, int v, int w)
{
    e[++k].to = v; e[k].next = h[u]; e[k].w = w; h[u] = k;
}
void dfs(int id, int val)
{
    dis[id] = val; vis[id] = true;
    for(int i = h[id]; i; i = e[i].next)
        if(!vis[e[i].to])
            dfs(e[i].to, val ^ e[i].w);
}
int main()
{
    scanf("%d", &n);
    int u, v, w;
    for(int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    dfs(1, 0); scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        printf("%d\n", dis[u] ^ dis[v]);
    }
}
