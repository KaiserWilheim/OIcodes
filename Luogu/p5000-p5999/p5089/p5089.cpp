#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m, q;
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
void soyuz(int a, int b)
{
	int pa = find(a), pb = find(b);
	if(pa != pb)p[pb] = pa;
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= m + n; i++)
		p[i] = i;
	for(int i = 1; i <= q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		soyuz(u, v + n);
	}
	int ans = -1;
	for(int i = 1; i <= n + m; i++)
		if(find(i) == i)ans++;
	printf("%d\n", ans);
	return 0;
}