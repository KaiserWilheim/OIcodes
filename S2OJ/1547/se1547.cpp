#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
int w[N];
vector<int>e[N];
ll f[N][2];
void add(int a, int b)
{
	e[a].push_back(b);
}
void dfs(int p, int fa)
{
	int k = e[p].size() / 2 + 1;
	ll res = 0;
	vector<ll>a;
	for(int i : e[p])
	{
		if(i == fa)continue;
		dfs(i, p);
		if(w[i] < w[p])
		{
			a.push_back(max(f[i][0] + w[i], f[i][1] + w[p]) - f[i][1] - m);
			res += f[i][1] + m;
		}
		else
		{
			a.push_back(f[i][0] + w[p] - max(f[i][0] + w[i], f[i][1] + m));
			res += max(f[i][0] + w[i], f[i][1] + m);
		}
	}
	sort(a.begin(), a.end(), greater<ll>());
	if(k - 1 > a.size())f[p][0] = -1e16;
	else
	{
		ll sum = res;
		for(int i = 0; i < k - 1; i++)sum += a[i];
		for(int i = k - 1; i < a.size(); i++)
			sum += max(0ll, a[i]);
		f[p][0] = sum;
	}
	if(k > a.size())f[p][1] = -1e16;
	else
	{
		ll sum = res;
		for(int i = 0; i < k; i++)sum += a[i];
		for(int i = k; i < a.size(); i++)
			sum += max(0ll, a[i]);
		f[p][1] = sum;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	printf("%lld\n", f[1][1]);
	return 0;
}