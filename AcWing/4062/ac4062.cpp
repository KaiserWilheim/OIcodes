#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = 1000010;
int n, m;
int v[M];
int x[N][N], ans;
map<int, int>dic;
int tot[M], cnt;
int cost[M];
bool chq(int a, int b, int c)
{
	if(a <= 0 || b <= 0 || c <= 0)return false;
	if(a >= b || a >= c || b >= c)return false;
	if(x[ans][1] == a && x[ans][2] == b && x[ans][3] == c)return false;
	ans++;
	x[ans][1] = a, x[ans][2] = b, x[ans][3] = c;
	return true;
}
int get_x()
{
	memset(cost, 0, sizeof(cost));
	cost[dic[x[ans][1] + x[ans][2]]]++;
	cost[dic[x[ans][1] + x[ans][3]]]++;
	cost[dic[x[ans][2] + x[ans][3]]]++;
	int now = 3;
	for(int i = 4; i <= n; i++)
	{
		while(tot[dic[v[now]]] - cost[dic[v[now]]] == 0)now++;
		x[ans][i] = v[now] - x[ans][1];
		for(int j = 1; j < i; j++)
		{
			int pos = dic[x[ans][i] + x[ans][j]];
			cost[pos]++;
			if(cost[pos] > tot[pos])return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	m = n * (n - 1) / 2;
	for(int i = 1; i <= m; i++)
		scanf("%d", &v[i]);
	sort(v + 1, v + 1 + m);
	for(int i = 1; i <= m; i++)
	{
		if(!dic[v[i]])dic[v[i]] = ++cnt;
		tot[dic[v[i]]]++;
	}
	for(int i = 3, a, b, c; i <= n; i++)
	{
		b = (v[i] - v[2] + v[1]) / 2;
		c = v[i] - b;
		a = v[1] - b;
		if(chq(a, b, c))ans -= get_x();
	}
	printf("%d\n", ans);
	for(int i = 1; i <= ans; i++)
	{
		for(int j = 1; j <= n; j++)
			printf("%d ", x[i][j]);
		putchar('\n');
	}
	return 0;
}
