#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 400010;
const int mod = 10000007;
int n, m;
int ans = 1;
int cnt;
int f[50];
int qpow(int a, int x)
{
	int res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
signed main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int k = 49; ~k; k--)
	{
		for(int i = 49; i; i--)
			f[i] += f[i - 1];
		if((n >> k) & 1)f[cnt++]++;
	}
	f[cnt]++;
	for(int i = 1; i <= 49; i++)
		ans = (ans * qpow(i, f[i])) % mod;
	cout << ans << endl;
	return 0;
}