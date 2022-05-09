#include<bits/stdc++.h>
using namespace std;
const int N = 1000, M = 1000000;
int n;
int h[N], e[M], ne[M], idx;
int q[N];
int d[N];

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void topsort()
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
}

int main()
{
	scanf("%d", &n);
	memset(h, -1, sizeof(h));
	for(int i = 1; i <= n; i++)
	{
		int son;
		while(scanf("%d", &son), son)
		{
			add(i, son);
			d[son]++;
		}
	}
	topsort();
	for(int i = 0; i < n; i++)printf("%d ",q[i]);
	putchar('\n');
	return 0;
}
