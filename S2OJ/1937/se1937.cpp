#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010;
int n, m;
struct AC
{
	int s[10];
	int fail;
	int cnt;
	double sum;
};
AC tr[N];
char s[N], ans[N];
int idx = 0, len;
void insert(double v)
{
	int p = 0;
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - '0';
		if(!tr[p].s[c])tr[p].s[c] = ++idx;
		p = tr[p].s[c];
	}
	tr[p].cnt++;
	tr[p].sum += v;
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 10; i++)
		if(tr[0].s[i])q.push(tr[0].s[i]);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		tr[p].sum += tr[tr[p].fail].sum;
		tr[p].cnt += tr[tr[p].fail].cnt;
		for(int i = 0; i < 10; i++)
		{
			if(!tr[p].s[i])tr[p].s[i] = tr[tr[p].fail].s[i];
			else tr[tr[p].s[i]].fail = tr[tr[p].fail].s[i], q.push(tr[p].s[i]);
		}
	}
}
double f[N][N];
int g[N][N][2];
char t[N];
double solve(double v)
{
	for(int i = 0; i <= idx; i++)tr[i].sum -= tr[i].cnt * v;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= idx; j++)
			f[i][j] = -1e100;
	f[0][0] = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= idx; j++)
		{
			if(f[i][j] < -1e99)continue;
			for(int k = 0; k < 10; k++)
			{
				if(t[i] == '.' || t[i] == k + '0')
				{
					int p = tr[j].s[k];
					if(f[i + 1][p] < f[i][j] + tr[p].sum)
					{
						f[i + 1][p] = f[i][j] + tr[p].sum;
						g[i + 1][p][0] = j, g[i + 1][p][1] = k;
					}
				}
			}
		}
	}
	for(int i = 0; i <= idx; i++)tr[i].sum += tr[i].cnt * v;
	int pos = 0;
	for(int i = 1; i <= idx; i++)
		if(f[n][i] > f[n][pos])pos = i;
	for(int i = n, p = pos; i; i--)
		ans[i] = g[i][p][1] + '0', p = g[i][p][0];
	return f[n][pos];
}
int main()
{
	scanf("%d%d", &n, &m);
	scanf("%s", t);
	for(int i = 1; i <= m; i++)
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		int x;
		scanf("%d", &x);
		insert(log(x));
	}
	get_fail();
	double l = 0, r = log(1e9 + 5), res = 0;
	while(r - l > 1e-4)
	{
		double mid = (l + r) / 2;
		if(solve(mid) > 0)res = mid, l = mid;
		else r = mid;
	}
	solve(res);
	printf("%s", ans + 1);
	return 0;
}
