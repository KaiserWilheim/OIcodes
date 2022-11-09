#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 3010;
const ll mod = 993244353;
int n;
char s[N];
char a[15] = " sakana", b[15] = " chinanago";
ll f[N][M];
bool chq(int l, bool type)
{
	if(type)
	{
		for(int i = 1; i <= 9; i++)
			if(s[l + i] != '?' && s[l + i] != b[i])
				return false;
	}
	else
	{
		for(int i = 1; i <= 6; i++)
			if(s[l + i] != '?' && s[l + i] != a[i])
				return false;
	}
	return true;
}
int main()
{
	cin >> n;
	cin >> s + 1;
	int k = n / 2, t = n / 5;
	f[0][k] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = k - t; j <= k + t; j++)
		{
			if(s[i] == '?')f[i][j] = (f[i][j] + f[i - 1][j] * 26 % mod) % mod;
			else f[i][j] = f[i - 1][j];
		}
		if(i >= 6 && chq(i - 6, 0))
		{
			for(int j = k - t; j <= k + t; j++)
			{
				f[i][j] = ((f[i][j] - f[i - 6][j]) % mod + mod) % mod;
				f[i][j + 1] = (f[i][j + 1] + f[i - 6][j]) % mod;
			}
		}
		if(i >= 9 && chq(i - 9, 1))
		{
			for(int j = k - t; j <= k + t; j++)
			{
				f[i][j] = ((f[i][j] - f[i - 9][j]) % mod + mod) % mod;
				f[i][j - 1] = (f[i][j - 1] + f[i - 9][j]) % mod;
			}
		}
	}
	cout << f[n][k] << endl;
	return 0;
}
