#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a, b, m, ans = 1;
const int mod = 9901;
int p[20], c[20];
void divide(int n)
{
	m = 0;
	for(int i = 2; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			p[++m] = i, c[m] = 0;
			while(n % i == 0)n /= i, c[m]++;
		}
	}
	if(n > 1)
		p[++m] = n, c[m] = 1;
}

int qpow(int a, ll b)
{
	int c = 1;
	while(b)
	{
		if(b & 1)c = ( ll )c * a % mod;
		a = ( ll )a * a % mod;
		b >>= 1;
	}
	return c;
}


int main()
{
	cin >> a >> b;
	if(a == 0)
	{
		puts("0");
		return 0;
	}
	else if(b == 0)
	{
		puts("1");
		return 0;
	}
	divide(a);
	for(int i = 1; i <= m; i++)
	{
		if((p[i] - 1) % mod == 0)
		{
			ans = (( ll )b * c[i] + 1) % mod * ans % mod;
			continue;
		}
		int x = qpow(p[i], ( ll )b * c[i] + 1);
		x = (x - 1 + mod) % mod;
		int y = p[i] - 1;
		y = qpow(y, mod - 2);
		ans = ( ll )ans * x % mod * y % mod;
	}
	cout << ans << endl;
	return 0;
}