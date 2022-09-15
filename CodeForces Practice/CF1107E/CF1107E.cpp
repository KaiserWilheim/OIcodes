#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n;
ll ans;
int a[N];
ll w[N];
ll f[N][N][N];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	string s;
	cin >> s;
	for(int i = 0; i < n; i++)
		a[i + 1] = s[i] - '0';
	for(int i = 1; i <= n; i++)
		cin >> w[i];
	for(int i = n; i; i--)
	{
		for(int j = i; j <= n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				f[i][j][k] = f[i][j - 1][0] + w[k + 1];
				for(int l = i; l < j; l++)
				{
					if(a[l] == a[j])
						f[i][j][k] = max(f[i][j][k], f[l + 1][j - 1][0] + f[i][l][k + 1]);
				}
			}
		}
	}
	cout << f[1][n][0] << endl;
	return 0;
}