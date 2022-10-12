#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, m;
ll mod;
int cntc[N];
ll f[N][N];
int main()
{
	scanf("%d%d%lld", &n, &m, &mod);
	for(int i = 1; i <= m; i++)
	{
		char s[N];
		int cntr = 0;
		scanf("%s", s + 1);
		for(int j = 1; j <= n; j++)
			cntc[j] += s[j] - '0', cntr += s[j] - '0';
		if(cntr != 2)
		{
			puts("0");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(cntc[i] > 2)
		{
			puts("0");
			return 0;
		}
	}
	if(m == n)
	{
		puts("1");
		return 0;
	}
	int cnt0 = 0, cnt1 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(cntc[i] == 0)cnt0++;
		else if(cntc[i] == 1)cnt1++;
	}
	f[cnt0][cnt1] = 1;
	for(int i = m + 1; i <= n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			int k = (n - i + 1) * 2 - j * 2;
			if(k > n || k < 0)continue;
			if(j >= 2)f[j - 2][k + 2] = (f[j - 2][k + 2] + f[j][k] * (j * (j - 1) / 2) % mod) % mod;
			if(k >= 2)f[j][k - 2] = (f[j][k - 2] + f[j][k] * (k * (k - 1) / 2) % mod) % mod;
			if(j >= 1 && k >= 1)f[j - 1][k] = (f[j - 1][k] + f[j][k] * j * k % mod) % mod;
		}
	}
	printf("%lld\n", f[0][0]);
	return 0;
}