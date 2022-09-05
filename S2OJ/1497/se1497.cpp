#include<bits/stdc++.h>
#include<random>
#include<chrono>
#define ull unsigned long long
using namespace std;
const int N = 1000010, M = N << 1;
const int L = 1010;
int n, m;
int h[N], e[M], ne[M], idx;
ull w[M];
void add(int a, int b, ull c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
ull sum[N];
map<int, ull>dic;
set<ull>s;
void dfs(int p, int fa, ull now)
{
	sum[p] = sum[fa] ^ now;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa)continue;
		dfs(j, p, w[i]);
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	mt19937_64 rand(chrono::system_clock::now().time_since_epoch().count());
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(!dic.count(w))
		{
			dic[w] = rand();
			s.insert(dic[w]);
		}
		ull k = dic[w];
		add(u, v, k), add(v, u, k);
	}
	dfs(1, 0, 0);
	long long a, b;
	scanf("%lld%lld", &a, &b);
	int ans = 0;
	while(m--)
	{
		int x = a % n + 1, y = b % n + 1;
		ull res = sum[x] ^ sum[y];
		if(res == 0 || s.count(res))ans++;
		a = (a * 666073) % 1000000007;
		b = (b * 233) % 998244353;
	}
	printf("%d\n", ans);
	return 0;
}