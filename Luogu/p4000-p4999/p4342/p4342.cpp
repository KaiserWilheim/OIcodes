#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 110;
int n;
int op[N], a[N];
ll f[N][N], g[N][N];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		op[i] = (s == "t") ? 1 : 2;
		op[i + n] = op[i];
		cin >> a[i];
		a[i + n] = a[i];
	}
	memset(f, 0xc1, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	for(int i = 1; i <= 2 * n - 1; i++)
	{
		f[i][i] = a[i];
		g[i][i] = a[i];
	}
	for(int len = 2; len <= n; len++)
	{
		for(int l = 1; l + len - 1 <= 2 * n - 1; l++)
		{
			int r = l + len - 1;
			for(int k = l + 1; k <= r; k++)
			{
				if(op[k] == 1)
				{
					f[l][r] = max(f[l][r], f[l][k - 1] + f[k][r]);
					g[l][r] = min(g[l][r], g[l][k - 1] + g[k][r]);
				}
				else
				{
					f[l][r] = max(f[l][r], f[l][k - 1] * f[k][r]);
					f[l][r] = max(f[l][r], g[l][k - 1] * g[k][r]);
					f[l][r] = max(f[l][r], f[l][k - 1] * g[k][r]);
					f[l][r] = max(f[l][r], g[l][k - 1] * f[k][r]);
					g[l][r] = min(g[l][r], f[l][k - 1] * f[k][r]);
					g[l][r] = min(g[l][r], g[l][k - 1] * g[k][r]);
					g[l][r] = min(g[l][r], f[l][k - 1] * g[k][r]);
					g[l][r] = min(g[l][r], g[l][k - 1] * f[k][r]);
				}
			}
		}
	}
	ll ans = INT64_MIN;
	vector<int>pos;
	for(int i = 1; i <= n; i++)
	{
		if(f[i][i + n - 1] > ans)
		{
			ans = f[i][i + n - 1];
			pos.clear();
			pos.push_back(i);
		}
		else if(f[i][i + n - 1] == ans)
			pos.push_back(i);
	}
	cout << ans << endl;
	for(int i : pos)cout << i << " ";
	cout << endl;
	return 0;
}