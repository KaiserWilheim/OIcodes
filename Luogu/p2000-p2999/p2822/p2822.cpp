#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll c[2010][2010];
ll ans[2010][2010];
ll k;
void getc()
{
	c[0][0] = 1;
	c[1][0] = c[1][1] = 1;
	for(int i = 2; i <= 2000; i++)
	{
		c[i][0] = 1;
		for(int j = 1; j <= i; j++)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
			ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
			if(!c[i][j])ans[i][j]++;
		}
		ans[i][i + 1] = ans[i][i];
	}
}
int main()
{
	int T;
	scanf("%d%lld", &T, &k);
	getc();
	while(T--)
	{
		int m, n;
		scanf("%d%d", &n, &m);
		printf("%lld\n", ans[n][(m > n) ? n : m]);
	}
	return 0;
}
