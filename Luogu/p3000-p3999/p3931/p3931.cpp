#include<bits/stdc++.h>
#define maxn 100005
#define maxe 200005
using namespace std;
int Q[maxn], Dep[maxn], n, T, S, x, y, z, tot = 1, lnk[maxn], nxt[maxe], son[maxe], w[maxe];
inline int read()
{
    int ret = 0; char ch = getchar();
    while(ch < '0' || ch>'9') ch = getchar();
    while(ch <= '9' && ch >= '0') ret = ret * 10 + ch - '0', ch = getchar();
    return ret;
}
inline void add(int x, int y, int z) { nxt[++tot] = lnk[x]; lnk[x] = tot; w[tot] = z; son[tot] = y; }
inline bool Bfs()
{
    memset(Dep, 0, sizeof Dep);
    int hed = 0, til = 1;
    Q[1] = S; Dep[S] = 1;
    while(hed != til)
    {
        hed++;
        for(int i = lnk[Q[hed]]; i; i = nxt[i])
            if(!Dep[son[i]] && w[i] > 0)
            {
                Dep[son[i]] = Dep[Q[hed]] + 1;
                Q[++til] = son[i];
            }
    }
    return Dep[T];
}
inline int Dfs(int x, int flow)
{
    if(x == T) return flow;
    int sum = 0;
    for(int i = lnk[x]; i && sum < flow; i = nxt[i])
        if(w[i] && Dep[son[i]] == Dep[x] + 1)
        {
            int Now = Dfs(son[i], min(w[i], flow - sum));
            w[i] -= Now, w[i ^ 1] += Now;
            sum += Now;
        }
    return sum;
}
inline int Dinic()
{
    int Ans = 0;
    while(Bfs()) Ans += Dfs(S, 1 << 30);
    return Ans;
}
inline void DFS(int x, int fa)
{
    bool flg = 0;
    for(int i = lnk[x]; i; i = nxt[i])
        if(son[i] != fa) flg = 1, w[i ^ 1] = 0, DFS(son[i], x);
    if(!flg) add(x, T, 1 << 30), add(T, x, 0);
}
int main()
{
    n = read(), S = read(); T = n + 1;
    for(int i = 1; i < n; i++) x = read(), y = read(), z = read(), add(x, y, z), add(y, x, z);
    DFS(S, 0);
    printf("%d", Dinic());
    return 0;
}
