#include<bits/stdc++.h>
const int N = 1000010, M = N << 1;
using namespace std;
int Q[N], Dep[N];
int n, T, S;
int h[N], ne[M], e[M], w[M], idx;
inline int read()
{
	int ret = 0; char ch = getchar();
	while(ch < '0' || ch>'9') ch = getchar();
	while(ch <= '9' && ch >= '0') ret = ret * 10 + ch - '0', ch = getchar();
	return ret;
}
inline void add(int x, int y, int z)
{
	ne[idx] = h[x]; h[x] = idx; w[idx] = z; e[idx++] = y;
}
inline bool Bfs()
{
	memset(Dep, 0, sizeof Dep);
	int hed = 0, til = 1;
	Q[1] = S; Dep[S] = 1;
	while(hed != til)
	{
		hed++;
		for(int i = h[Q[hed]]; ~i; i = ne[i])
			if(!Dep[e[i]] && w[i] > 0)
			{
				Dep[e[i]] = Dep[Q[hed]] + 1;
				Q[++til] = e[i];
			}
	}
	return Dep[T];
}
inline int Dfs(int x, int flow)
{
	if(x == T) return flow;
	int sum = 0;
	for(int i = h[x]; ~i && sum < flow; i = ne[i])
		if(w[i] && Dep[e[i]] == Dep[x] + 1)
		{
			int Now = Dfs(e[i], min(w[i], flow - sum));
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
	for(int i = h[x]; ~i; i = ne[i])
		if(e[i] != fa) flg = 1, w[i ^ 1] = 0, DFS(e[i], x);
	if(!flg) add(x, T, 1 << 30), add(T, x, 0);
}
int main()
{
	memset(h, -1, sizeof(h));
	n = read(), S = read();
	T = n + 1;
	for(int i = 1; i < n; i++)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z), add(y, x, z);
	}
	DFS(S, 0);
	printf("%d", Dinic());
	return 0;
}
