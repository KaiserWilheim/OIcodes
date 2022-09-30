#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
#define lowbit(x) (x&(-x))
int n;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
string s;
int tag[N];
ll f[N][2];
ll ans = 0;
void dfs(int p, int fa)
{
	f[p][0] = 0, f[p][1] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		int j = e[i];
		dfs(j, p);
		int tmp0 = INT_MAX, tmp1 = INT_MAX;
		tmp0 = min(f[p][0] + f[j][0], f[p][1] + f[j][1]);
		tmp1 = min(min(f[p][0] + f[j][1], f[p][1] + f[j][0]), f[p][1] + f[j][1]);
		f[p][0] = tmp0, f[p][1] = tmp1;
	}
	if(tag[p])f[p][0] = INT_MAX;
	else f[p][1] = INT_MAX;
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		h[i] = -1;
	cin >> s;
	for(int i = 1; i <= n; i++)
		tag[i] = s[i - 1] - '0';
	vector<int>v;
	for(int i = 1; i <= n; i++)
	{
		int k = i + lowbit(i);
		if(k > n)v.push_back(i);
		else add(i, k), add(k, i);
	}
	for(auto i : v)
	{
		dfs(i, 0);
		ans += min(f[i][0], f[i][1]);
	}
	printf("%lld\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		ans = 0;
		solve();
	}
	return 0;
}