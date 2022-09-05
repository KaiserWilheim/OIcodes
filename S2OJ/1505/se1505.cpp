#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int a[N], b[N];
int sa[N], sb[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	a[0] = b[0] = -114514;
	for(int i = 1; i <= n; i++)
		sa[i] = sa[i - 1] + (a[i] != a[i - 1]);
	sa[n + 1] = sa[n] + (a[n] != a[1]);
	for(int i = 2; i <= n; i++)
		sa[i + n] = sa[i - 1 + n] + (a[i] != a[i - 1]);
	for(int i = 1; i <= m; i++)
		sb[i] = sb[i - 1] + (b[i] != b[i - 1]);
	sb[m + 1] = sb[m] + (b[m] != b[1]);
	for(int i = 2; i <= m; i++)
		sb[i + m] = sb[i - 1 + m] + (b[i] != b[i - 1]);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int xs, xe, ys, ye;
		scanf("%d%d%d%d", &xs, &ys, &xe, &ye);
		if(xs > xe)swap(xs, xe);
		if(ys > ye)swap(ys, ye);
		int ans = min(sa[xe] - sa[xs], sa[xs + n] - sa[xe]) + min(sb[ye] - sb[ys], sb[ys + m] - sb[ye]);
		printf("%d\n", ans);
	}
	return 0;
}