#include <bits/stdc++.h>
using namespace std;
const int N = 2000010;
struct query
{
	int x, y, e;
}qwert[N];
int n, m;
int f[N];
map<int, int>dic;
int getlisan(int x)
{
	if(dic.count(x) == 0)dic.insert(make_pair(x, ++n));
	return (*dic.find(x)).second;
}
int getanc(int x)
{
	if(f[x] != x)f[x] = getanc(f[x]);
	return f[x];
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		n = 0;
		dic.clear();
		scanf("%d", &m);
		for(int i = 1; i <= m; i++)
		{
			int x, y, e;
			scanf("%d%d%d", &x, &y, &e);
			qwert[i] = { getlisan(x),getlisan(y),e };
		}
		for(int i = 1; i <= n; i++)f[i] = i;
		for(int i = 1; i <= m; i++)
		{
			if(qwert[i].e == 1)
			{
				int pa = getanc(qwert[i].x), pb = getanc(qwert[i].y);
				f[pb] = pa;
			}
		}
		bool conflict = false;
		for(int i = 1; i <= m; i++)
		{
			if(qwert[i].e == 0)
			{
				int pa = getanc(qwert[i].x), pb = getanc(qwert[i].y);
				if(pa == pb)
				{
					conflict = true;
					break;
				}
			}
		}
		if(conflict)puts("NO");
		else puts("YES");
	}
	return 0;
}
