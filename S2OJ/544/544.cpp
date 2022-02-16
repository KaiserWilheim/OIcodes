#include<bits/stdc++.h>
#define ll long long
const int N = 100010;
using namespace std;
ll n, m;
ll chq, ans, temp;
ll t[N], p[N], maxp[N];
char s[N << 1];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		cin >> s + 1 >> t[i];
		int lens = strlen(s + 1);
		for(int j = lens; j >= 1; j--)
		{
			p[i] += (s[j] == 'F' ? -1 : 1);
			maxp[i] = max(p[i], maxp[i]);
		}
		chq += p[i] * t[i];
	}
	if(chq > 0)
	{
		puts("-1");
		return 0;
	}
	ans = 1;
	for(int i = m; i >= 1; i--)
	{
		if(p[i] > 0)
		{
			ans = max(ans, temp + (t[i] - 1) * p[i] + maxp[i]);
		}
		else
		{
			ans = max(ans, temp + maxp[i]);
		}
		temp += p[i] * t[i];
	}
	printf("%lld", ans - 1);
	return 0;
}
