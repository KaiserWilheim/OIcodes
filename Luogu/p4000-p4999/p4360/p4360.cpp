#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 30010;
int n, m;
int w[N], dis[N];
int sum[N], tot;
double calc(int j, int k) { return 1.0 * (dis[j] * sum[j] - dis[k] * sum[k]) / (sum[j] - sum[k]); }
int count(int i, int j) { return tot - dis[j] * sum[j] - dis[i] * (sum[i] - sum[j]); }
int q[N], hh, tt;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &w[i], &dis[i]);
	for(int i = n; i >= 1; i--)dis[i] += dis[i + 1];
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + w[i], tot += dis[i] * w[i];
	int ans = INT_MAX;
	for(int i = 1; i <= n; i++)
	{
		while(tt > hh && calc(q[hh], q[hh + 1]) > dis[i])hh++;
		ans = min(ans, count(i, q[hh]));
		while(hh < tt && calc(q[tt - 1], q[tt]) < calc(q[tt], i))tt--;
		q[++tt] = i;
	}
	printf("%d\n", ans);
	return 0;
}
