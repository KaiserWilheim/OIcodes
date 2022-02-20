#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m, k;
struct Edge
{
	int a, b, w;
	bool operator < (const Edge &a) const
	{
		return w > a.w;
	}
}e[N];
struct Quest
{
	int k, v, i;
	bool operator < (const Quest &a) const
	{
		return k > a.k;
	}
}q[N];
int p[N], num[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int ans[N];
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++)p[i] = i, num[i] = 1;
	m = n - 1;
	for(int i = 1; i <= m; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		e[i] = { a,b,w };
	}
	for(int i = 1; i <= k; i++)
	{
		int ki, vi;
		scanf("%d%d", &ki, &vi);
		q[i] = { ki,vi,i };
	}
	sort(e + 1, e + 1 + m);
	sort(q + 1, q + 1 + k);
	int idx = 1;
	/*for(int i = 1; i <= m; i++)
	{
		int a = e[i].a, b = e[i].b, w = e[i].w;
		while((w < q[idx].k) && (idx <= k))
		{
			ans[q[idx].i] = num[find(q[idx].v)];
			idx++;
		}
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			num[a] += num[b];
		}
	}*/
	int j = 1;
	for(int i = 1; i <= k; i++)
	{
		while((j <= m) && (e[j].w >= q[i].k))
		{
			int pa = find(e[j].a), pb = find(e[j].b);
			if(pa != pb)
			{
				p[pa] = pb;
				num[pb] += num[pa];
			}
			j++;
		}
		ans[q[i].i] = num[find(q[i].v)];
	}
	for(int i = 1; i <= k; i++)
	{
		printf("%d\n", ans[i]-1);
	}
	return 0;
}
