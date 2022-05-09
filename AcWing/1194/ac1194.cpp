#include<bits/stdc++.h>
using namespace std;
const int N = 10010, M = 100010;
int n, m;
int h[N], e[M], ne[M], idx;
int q[N];
int d[N];
int dis[N];

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool topsort()
{
	int hh = 0, tt = -1;
	for(int i = 1; i <= n; i++)
		if(!d[i])
			q[++tt] = i;

	while(hh <= tt)
	{
		int t = q[hh++];
		for(int i = h[t]; ~i; i = ne[i])
		{
			int j = e[i];
			if(--d[j] == 0)
				q[++tt] = j;
		}
	}
	return tt == n - 1;
}

int main()
{
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof(h));
	while(m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(b, a);
		d[a]++;
	}
	if(!topsort())
	{
		puts("Poor Xed");
	}
	else
	{
		for(int i = 1; i <= n; i++)dis[i] = 100;
		for(int i = 0; i < n; i++)
		{
			int j = q[i];
			for(int k = h[j]; ~k; k = ne[k])
				dis[e[k]] = max(dis[e[k]], dis[j] + 1);
		}
		int res = 0;
		for(int i = 1; i <= n; i++)res += dis[i];
		printf("%d\n", res);
	}
	return 0;
}
