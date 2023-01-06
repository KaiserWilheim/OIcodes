#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int idx = 1;
int fa[N];
double f[N][65];
int main()
{
	scanf("%d", &m);
	for(int i = 1; i <= 60; i++)f[1][i] = 1;
	while(m--)
	{
		int op, x;
		scanf("%d%d", &op, &x);
		if(op == 1)
		{
			vector<int>v;
			fa[++idx] = x;
			x = idx;
			for(int i = 1; i <= 60; i++)f[x][i] = 1;
			for(int i = 1; i <= 61 && x; i++)
				v.push_back(x), x = fa[x];
			for(int i = v.size() - 2; i; i--)
				f[v[i + 1]][i + 1] /= (f[v[i]][i] + 1) / 2.0;
			for(int i = 0; i < v.size() - 1; i++)
				f[v[i + 1]][i + 1] *= (f[v[i]][i] + 1) / 2.0;
		}
		else
		{
			double ans = 59;
			for(int i = 1; i < 60; i++)ans -= f[x][i];
			printf("%.9lf\n", ans);
		}
	}
	return 0;
}
