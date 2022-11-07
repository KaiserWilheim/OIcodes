#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
const ll mod = 114514;
int n;
char s[N];
int a[N];
ll f1[N][26], f2[26][26];
ll g1[N][26], g2[26][26];
ll cnt[26][26];
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		a[i] = s[i] - 'a';
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 26; j++)
			f1[i][j] = f1[i - 1][j] + (a[i] == j);
	for(int i = n; i >= 1; i--)
		for(int j = 0; j < 26; j++)
			g1[i][j] = g1[i + 1][j] + (a[i] == j);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 26; j++)
			cnt[a[i]][j] += f1[i - 1][j];
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < 26; j++)
		{
			if(a[i] == j)continue;
			for(int k = 0; k < 26; k++)
			{
				if(a[i] == k || k == j)continue;
				ans = (ans + f2[j][k] * (cnt[j][k] - g2[j][k] - f1[i - 1][k] * g1[i + 1][j])) % mod;
			}
		}
		for(int j = 0; j < 26; j++)
			f2[a[i]][j] = (f2[a[i]][j] + g2[j][j]) % mod;
		for(int j = 0; j < 26; j++)
			g2[a[i]][j] = (g2[a[i]][j] + f1[i - 1][j]);
	}
	printf("%lld\n", ans);
	return 0;
}