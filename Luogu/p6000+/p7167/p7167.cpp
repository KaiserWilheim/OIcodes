#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010;
const int INF = 0x3f3f3f3f;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch>'9') { if(ch == '-')f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); }
	return x * f;
}
int n, m;
int d[N], c[N];
int ne[N][100], u[N][100];
int q[N];
int tt;
int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		d[i] = read(), c[i] = read();
	for(int i = n; i > 0; i--)
	{
		while(tt > 0 && d[i] >= d[q[tt]])tt--;
		ne[i][0] = q[tt];
		q[++tt] = i;
	}
	for(int j = 1; j <= 23; j++)
		for(int i = 1; i <= n; i++)
			ne[i][j] = ne[ne[i][j - 1]][j - 1];
	for(int i = 1; i <= n; i++)
		u[i][0] = c[ne[i][0]];
	for(int i = 1; i <= n; i++)
		if(ne[i][0] == 0)
			u[i][0] = INF;
	for(int j = 1; j <= 23; j++)
		for(int i = 1; i <= n; i++)
			u[i][j] = u[i][j - 1] + u[ne[i][j - 1]][j - 1];

	while(m--)
	{
		int r = read(), v = read();
		if(v <= c[r])
		{
			printf("%d\n", r);
			continue;
		}
		v -= c[r];
		for(int i = 23; i >= 0; i--)
			if(u[r][i] <= v)
				v -= u[r][i], r = ne[r][i];
		if(v > 0)r = ne[r][0];
		printf("%d\n", r);
	}
	return 0;
}
