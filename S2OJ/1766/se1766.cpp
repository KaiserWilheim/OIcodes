#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int N = 100010, M = N << 1;
#define lowbit(x) ((x)&(-(x)))
int n, m;
int f[N], t[N];
int a[N], b[N], c[N], d[N];
int id1[N], id2[N];
ll tr[N], ans[N];
void segadd(int x, int c)
{
	for(int i = x; i <= m; i += lowbit(i))
		tr[i] += c;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
void add(int x) { segadd(t[x], f[x]); }
void del(int x) { segadd(t[x], -f[x]); }
int tmp[N];
bool cmp1(int lhs, int rhs) { return c[lhs] < c[rhs]; }
bool cmp2(int lhs, int rhs) { return t[lhs] < t[rhs]; }
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &f[i]);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &t[i]);
		tmp[i] = t[i];
	}
	sort(tmp + 1, tmp + 1 + n);
	m = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
		id1[i] = id2[i] = i;
		t[i] = lower_bound(tmp + 1, tmp + 1 + m, t[i]) - tmp;
		a[i] = lower_bound(tmp + 1, tmp + 1 + m, a[i]) - tmp;
		b[i] = upper_bound(tmp + 1, tmp + 1 + m, b[i]) - tmp - 1;
		c[i] = lower_bound(tmp + 1, tmp + 1 + m, c[i]) - tmp;
		d[i] = upper_bound(tmp + 1, tmp + 1 + m, d[i]) - tmp - 1;
	}
	sort(id1 + 1, id1 + 1 + n, cmp1);
	sort(id2 + 1, id2 + 1 + n, cmp2);
	priority_queue<pii, vector<pii>, greater<pii>>q;
	int now = 1;
	for(int i = 1; i <= n; i++)
	{
		while(now <= n && c[id1[now]] <= t[id2[i]])
		{
			if(d[id1[now]] >= t[id2[i]])
			{
				add(id1[now]);
				q.emplace(d[id1[now]], id1[now]);
			}
			now++;
		}
		while(!q.empty() && q.top().first < t[id2[i]])
		{
			del(q.top().second);
			q.pop();
		}
		ans[id2[i]] = segsum(b[id2[i]]) - segsum(a[id2[i]] - 1);
	}
	for(int i = 1; i <= n; i++)
	{
		if(t[i] < c[i] || d[i] < t[i] || t[i] < a[i] || b[i] < t[i])
			ans[i] += f[i];
		printf("%lld ", ans[i]);
	}
	putchar('\n');
	return 0;
}