#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
inline int read()
{
	int x = 0; char c = getchar();
	while (!isdigit(c))c = getchar();
	while (isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int a[N];
struct Num
{
	int m[100];
	Num() { memset(m, 0, sizeof(m)); }
	friend int operator | (Num a, int b)
	{
		Num c = a;
		for (int i = 0; b; b >>= 1, i++)
			c.m[i] += (b & 1) ? 1 : 0;
		int res = 0;
		for (int i = 32; i >= 0; i--)
		{
			res <<= 1;
			res += (c.m[i] > 0) ? 1 : 0;
		}
		return res;
	}
	void oor(int b)
	{
		for (int i = 0; b; b >>= 1, i++)
			m[i] += (b & 1) ? 1 : 0;
	}
	void dor(int b)
	{
		for (int i = 0; b; b >>= 1, i++)
		{
			m[i] -= (b & 1) ? 1 : 0;
			if (m[i] < 0)m[i] = 0;
		}
	}
};
ll ans;
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	Num res;
	int tt = 0;
	for (int i = 1; i <= n; i++)
	{
		while ((res | a[tt + 1]) < m && tt < n)res.oor(a[++tt]);
		if (tt < i)tt = i;
		ans += (tt - i);
		res.dor(a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}