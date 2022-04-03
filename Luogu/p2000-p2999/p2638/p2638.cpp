#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
ll c[2010][2010];
ll ans[2010][2010];
void getc()
{
	c[0][0] = 1;
	c[1][0] = c[1][1] = 1;
	for(int i = 2; i <= 50; i++)
	{
		c[i][0] = 1;
		for(int j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
}
int main()
{
	getc();
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	ll ans = 0;
	for(int i = 0; i <= a; i++)
		for(int j = 0; j <= b; j++)
			ans += c[n + i - 1][n - 1] * c[n + j - 1][n - 1];
	cout << ans << endl;
	return 0;
}
