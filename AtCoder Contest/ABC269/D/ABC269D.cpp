#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n;
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
map<pair<int, int>, int>dic;
int x[N], y[N];
int xx[7] = { 0,1,1,0,-1,-1 }, yy[7] = { 1,1,0,-1,-1,0 };
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		p[i] = i;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		dic.emplace(make_pair(x[i], y[i]), i);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			int nx = x[i] + xx[j], ny = y[i] + yy[j];
			if(dic.count(make_pair(nx, ny)))
			{
				int pa = find(i), pb = find(dic.find(make_pair(nx, ny))->second);
				p[pb] = pa;
			}
		}
	}
	int tot = n;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) != i)tot--;
	}
	printf("%d\n", tot);
	return 0;
}