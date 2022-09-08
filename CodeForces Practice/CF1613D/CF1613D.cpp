#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
const ll mod = 998244353;
int n, m;
ll f[N][2];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n;
		for(int i = 0; i <= n; i++)f[i][0] = f[i][1] = 0;
		f[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			f[x + 1][0] = f[x + 1][0] * 2 % mod;
			f[x + 1][1] = f[x + 1][1] * 2 % mod;
			f[x + 1][0] = (f[x + 1][0] + f[x][0]) % mod;
			if(x)
			{
				f[x - 1][1] = f[x - 1][1] * 2 % mod;
				f[x - 1][1] = (f[x - 1][1] + f[x - 1][0]) % mod;
			}
		}
		ll res = 0;
		for(int i = 0; i <= n; i++)
			res = (res + f[i][0] + f[i][1]) % mod;
		cout << (res - 1 + mod) % mod << endl;
	}
	return 0;
}