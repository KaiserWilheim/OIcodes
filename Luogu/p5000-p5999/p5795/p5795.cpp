#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n, m;
int x[N], y[N];
int tr[N * 34][2], sum[N * 34];
int pt[N][2];
int rt[N], idx;
int insert(int q, int v)
{
	int p = ++idx, res = p;
	for(int i = 31; i >= 0; i--)
	{
		int c = (v >> i) & 1;
		tr[p][c ^ 1] = tr[q][c ^ 1];
		q = tr[q][c];
		p = tr[p][c] = ++idx;
		sum[p] = sum[q] + 1;
	}
	return res;
}
int solve(int u, int d, int l, int r, int k)
{
	k = (d - u + 1) * (r - l + 1) - k + 1;
	for(int i = u; i <= d; i++)
	{
		pt[i][0] = rt[l - 1];
		pt[i][1] = rt[r];
	}
	int res = 0;
	for(int s = 31; s >= 0; s--)
	{
		int cnt = 0;
		for(int i = u; i <= d; i++)
		{
			int c = (x[i] >> s) & 1;
			cnt += sum[tr[pt[i][1]][c]] - sum[tr[pt[i][0]][c]];
		}
		int ne = (k <= cnt ? 0 : 1);
		if(ne)k -= cnt;
		res = (res << 1) | ne;
		for(int i = u; i <= d; i++)
		{
			int c = ((x[i] >> s) & 1) ^ ne;
			pt[i][0] = tr[pt[i][0]][c];
			pt[i][1] = tr[pt[i][1]][c];
		}
	}
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &y[i]);
	for(int i = 1; i <= m; i++)
		rt[i] = insert(rt[i - 1], y[i]);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int u, d, l, r, k;
		scanf("%d%d%d%d%d", &u, &d, &l, &r, &k);
		printf("%d\n", solve(u, d, l, r, k));
	}
	return 0;
}
