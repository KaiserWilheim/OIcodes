#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 30010;
const ll base = 2333;
int n, m;
string s[N];
ll h[N];
ll t[N];
ll qpow[N];
int main()
{
	{
		int tmp;
		cin >> n >> m >> tmp;
	}
	for(int i = 1; i <= n; i++)cin >> s[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			h[i] = (h[i] * base + s[i][j - 1]);
	qpow[0] = 1;
	for(int i = 1; i <= m; i++)
		qpow[i] = qpow[i - 1] * base;
	int ans = 0;
	for(int k = 1; k <= m; k++)
	{
		for(int i = 1; i <= n; i++)
			t[i] = h[i] - s[i][k - 1] * qpow[m - k];
		sort(t + 1, t + 1 + n);
		int tmp = 1;
		for(int i = 1; i < n; i++)
		{
			if(t[i] != t[i + 1])tmp = 1;
			else
			{
				ans += tmp;
				tmp++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}