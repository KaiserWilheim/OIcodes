#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = 2020;
int n, k;
int h[N], e[M], ne[M], idx;
int md;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p, int vater, int depth)
{
	md = max(md, depth);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == vater) continue;
		dfs(j, p, depth + 1);
	}
	return;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(0, -1, 1);
	if(k <= md) cout << k + 1 << endl;
	else cout << min(n, md + (k - md + 1) / 2) << endl;
	return 0;
}
