#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 400010, M = N << 1;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
struct trie
{
	int s[15];
	int w;
	int fail;
}tr[N];
int idx = 0;
char s[N];
void insert(char *s, int k)
{
	int p = 0, len = strlen(s + 1);
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - 'a';
		if(!tr[p].s[c])tr[p].s[c] = ++idx;
		p = tr[p].s[c];
	}
	tr[p].w += k;
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 14; i++)
		if(tr[0].s[i])q.push(tr[0].s[i]);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = 0; i < 14; i++)
		{
			if(tr[p].s[i])
			{
				tr[tr[p].s[i]].fail = tr[tr[p].fail].s[i];
				q.push(tr[p].s[i]);
			}
			else
			{
				tr[p].s[i] = tr[tr[p].fail].s[i];
			}
		}
		tr[p].w += tr[tr[p].fail].w;
	}
}
int pos[N], l[N], r[N], tt, cnt;
int to[N][20], num[N][20];
ll f[2][17000][1010];
void solve(int d, int p)
{
	int sum = 0, k1 = p, k2 = d;
	for(int i = l[d]; i <= r[d]; i++)
		p = tr[p].s[s[i] - 'a'], sum += tr[p].w;
	to[k1][k2] = p, num[k1][k2] = sum;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int w;
		scanf("%s%d", s + 1, &w);
		insert(s, w);
	}
	get_fail();
	scanf("%s", s + 1);
	m = strlen(s + 1);
	for(int i = 1; i <= m; i++)
	{
		if(s[i] == '?')pos[++tt] = i;
		else
		{
			if(i == 1 || s[i - 1] == '?')l[++cnt] = i;
			if(i == m || s[i + 1] == '?')r[cnt] = i;
		}
	}
	for(int i = 1; i <= cnt; i++)
		for(int j = 0; j <= idx; j++)
			solve(i, j);
	r[cnt + 1] = 1e9;
	int p = 0;
	memset(f[0], -63, sizeof(f[0]));
	f[0][0][0] = 0;
	for(int i = 1; i <= tt; i++)
	{
		int x = pos[i], now = i & 1;
		if(r[p + 1] < x)p++;
		memset(f[now], -63, sizeof(f[now]));
		for(int S = 0; S < (1 << 14); S++)
		{
			for(int k = 0; k < 14; k++)
			{
				if(S & (1 << k))continue;
				for(int j = 0; j <= idx; j++)
				{
					if(f[now ^ 1][S][j] > -1e18)
					{
						int q = j, sum = 0;
						if(r[p] < x)q = to[j][p], sum += num[j][p];
						q = tr[q].s[k], sum += tr[q].w;
						f[now][S | (1 << k)][q] = max(f[now][S | (1 << k)][q], f[now ^ 1][S][j] + sum);
					}
				}
			}
		}
	}
	ll ans = -INF;
	for(int i = 0; i <= idx; i++)
	{
		if(p == cnt)
			for(int S = 0; S < (1 << 14); S++)
				ans = max(ans, f[tt & 1][S][i]);
		if(p != cnt)
			for(int S = 0; S < (1 << 14); S++)
				ans = max(ans, f[tt & 1][S][i] + num[i][cnt]);
	}
	printf("%lld\n", ans);
	return 0;
}
