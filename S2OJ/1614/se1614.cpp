#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500010;
vector<int>daor(vector<int>a, vector<int>b)
{
	int n = a.size();
	if(n <= 16)
	{
		vector<int>c(n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				c[i | j] = max(c[i | j], a[i] + b[j]);
		return c;
	}
	vector<int>x(n / 2), y(n / 2);
	int m = n / 2;
	for(int i = 0; i < m; i++)
	{
		x[i] = a[i];
		y[i] = b[i];
	}
	vector<int>res1 = daor(x, y);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[m + i];
		y[i] = max(b[i], b[m + i]);
	}
	vector<int>res2 = daor(x, y);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[i];
		y[i] = b[m + i];
	}
	vector<int>res3 = daor(x, y);
	vector<int>c(n);
	for(int i = 0; i < m; i++)
		c[i] = res1[i];
	for(int i = 0; i < m; i++)
		c[m + i] = max(res2[i], res3[i]);
	return c;
}
signed main()
{
	int n;
	scanf("%lld", &n);
	n = (1 << n);
	vector<int>a, b;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%lld", &x);
		a.push_back(x);
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%lld", &x);
		b.push_back(x);
	}
	vector<int>c = daor(a, b);
	for(auto i : c)
		printf("%lld ", i);
	putchar('\n');
	return 0;
}