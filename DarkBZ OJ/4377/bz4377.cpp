#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
int a, b, p;
int l[N], r[N];
int pr[N];
int d[M], cnt;
int c[M];
int ans;
int main()
{
	scanf("%d%d%d%d%d", &n, &a, &b, &p, &m);
	string s;
	cin >> s;
	for(int i = 1; i <= m; i++)
	{
		int B = (1ll * i * a + b) % n;
		if(s[i - 1] == '1')
		{
			l[i] = p - B - 1;
			r[i] = n - B - 1;
			if(l[i] < 0)l[i] += n;
		}
		else
		{
			l[i] = n - B - 1;
			r[i] = p - B - 1;
			if(r[i] < 0)r[i] += n;
		}
		d[++cnt] = l[i], d[++cnt] = r[i];
	}
	for(int i = n - m + 1; i <= n - 1; i++)pr[n - i] = 1ll * a * i % n;
	sort(d + 1, d + 1 + cnt);
	sort(pr + 1, pr + m);
	cnt = unique(d + 1, d + 1 + cnt) - d - 1;
	if(d[cnt] != n - 1)d[++cnt] = n - 1;
	for(int i = 1; i <= m; i++)
	{
		c[lower_bound(d + 1, d + 1 + cnt, l[i]) - d]--;
		c[lower_bound(d + 1, d + 1 + cnt, r[i]) - d]++;
		if(l[i] > r[i])c[cnt]++;
	}
	d[0] = -1;
	for(int i = cnt, r = m - 1; i; i--)
	{
		c[i] += c[i + 1];
		int l = r;
		while(l && pr[l] > d[i - 1])l--;
		if(c[i] == m)ans += d[i] - d[i - 1] - r + l;
		r = l;
	}
	printf("%d\n", ans);
	return 0;
}