#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int a[N], b[N];
int l[N], r[N];
int prf[N], suf[N];
int sta[N], tt;
int ans[N], cnt = 0;
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		b[i] = read();
	}
	int m = 0;
	for(int i = 1; i <= n; i++)
	{
		if(b[i] != b[l[m]])
		{
			r[m] = i - 1;
			l[++m] = i;
			a[m] = b[i];
		}
	}
	r[m] = n, l[m + 1] = n + 1;
	sta[0] = 0;
	for(int i = 1; i <= m; i++)
	{
		while(tt && a[sta[tt]] % a[i] == 0)tt--;
		prf[i] = l[i] - r[sta[tt]] - 1;
		sta[++tt] = i;
	}
	tt = 0;
	sta[0] = m + 1;
	for(int i = m; i >= 1; i--)
	{
		while(tt && a[sta[tt]] % a[i] == 0)tt--;
		suf[i] = l[sta[tt]] - r[i] - 1;
		sta[++tt] = i;
	}
	int maxn = 0;
	for(int i = 1; i <= m; i++)
		maxn = max(maxn, prf[i] + suf[i] + r[i] - l[i]);
	for(int i = 1; i <= m; i++)
		if(prf[i] + suf[i] + r[i] - l[i] == maxn)
			if(cnt == 0 || ans[cnt] != l[i] - prf[i])
				ans[++cnt] = l[i] - prf[i];
	printf("%d %d\n", cnt, maxn);
	for(int i = 1; i <= cnt; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}