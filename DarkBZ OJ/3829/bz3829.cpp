#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
template<typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-')f = -1; c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
int n;
vector<int>e[N];
int val[N];
int f[N], sz[N];
bool cmp(const int a, const int b)
{
	return sz[a] - f[a] < sz[b] - f[b];
}
void dfs(int p, int fa)
{
	if(p != 1)f[p] = val[p];
	if(e[p].empty())return;
	for(auto i : e[p])
		if(i != fa)dfs(i, p);
	sort(e[p].begin(), e[p].end(), cmp);
	for(auto i : e[p])
	{
		if(i == fa)continue;
		f[p] = max(f[p], f[i] + sz[p] + 1);
		sz[p] += sz[i] + 2;
	}
}
int main()
{
	n = read<int>();
	for(int i = 1; i <= n; i++)
		val[i] = read<int>();
	for(int i = 1; i < n; i++)
	{
		int u = read<int>(), v = read<int>();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	printf("%d\n", max(f[1], sz[1] + val[1]));
	return 0;
}
