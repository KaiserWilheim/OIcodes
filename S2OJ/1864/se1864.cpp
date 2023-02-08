#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010, M = 3010;
int n, m, k;
int a[N];
char s[N];
int sum[N];
int f[N], g[N];
deque<int>q;
void solve()
{
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + s[i] - '0';
	f[0] = 0;
	q.clear();
	q.push_back(0);
	for(int i = 1; i <= n; i++)
	{
		while(!q.empty() && (q.front() < i - k || sum[i - 1] - sum[q.front()]))q.pop_front();
		f[i] = f[q.front()] + a[i];
		while(!q.empty() && f[q.back()] >= f[i])q.pop_back();
		q.push_back(i);
	}
	g[n + 1] = 0;
	q.clear();
	q.push_back(n + 1);
	for(int i = n; i >= 1; i--)
	{
		while(!q.empty() && (q.front() > i + k || sum[q.front() - 1] - sum[i]))q.pop_front();
		g[i] = g[q.front()] + a[i];
		while(!q.empty() && g[q.back()] >= g[i])q.pop_back();
		q.push_back(i);
	}
	scanf("%lld", &m);
	while(m--)
	{
		int pos; int val;
		int ans = 1e18;
		scanf("%lld%lld", &pos, &val);
		int tmp = a[pos];
		vector<int>arr;
		q.clear();
		q.push_back(max(0ll, pos - k));
		for(int i = max(0ll, pos - k) + 1; i < pos; i++)
		{
			while(!q.empty() && (q.front() < i - k || sum[i - 1] - sum[q.front()]))q.pop_front();
			while(!q.empty() && f[q.back()] >= f[i])q.pop_back();
			q.push_back(i);
		}
		a[pos] = val;
		for(int i = pos; i <= min(n + 1, pos + k - 1); i++)
		{
			while(!q.empty() && (q.front() < i - k || sum[i - 1] - sum[q.front()]))q.pop_front();
			arr.push_back(f[i]);
			f[i] = f[q.front()] + a[i];
			while(!q.empty() && f[q.back()] >= f[i])q.pop_back();
			q.push_back(i);
		}
		g[pos] -= tmp - a[pos];
		for(int i = pos; i <= min(n + 1, pos + k - 1); i++)
			ans = min(ans, f[i] + g[i] - a[i]);
		g[pos] += tmp - a[pos];
		printf("%lld\n", ans);
		a[pos] = tmp;
		for(int i = pos; i <= min(n + 1, pos + k - 1); i++)
			f[i] = arr[i - pos];
	}
}
signed main()
{
	int T;
	scanf("%lld", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
