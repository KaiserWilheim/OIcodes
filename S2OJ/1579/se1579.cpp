#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500010;
int mex[3][3] = { {1,2,1},{2,0,0},{1,0,0} };
vector<int>daor(vector<int>a, vector<int>b)
{
	int n = a.size();
	if(n <= 3)
	{
		vector<int>c(n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				c[mex[i][j]] = c[mex[i][j]] + a[i] * b[j];
		return c;
	}
	int m = n / 3;
	vector<int>x(m), y(m);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[m + i] + a[m * 2 + i];
		y[i] = b[m + i] + b[m * 2 + i];
	}
	vector<int>res1 = daor(x, y);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[i];
		y[i] = b[i] + b[m * 2 + i];
	}
	vector<int>res2 = daor(x, y);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[m * 2 + i];
		y[i] = b[i];
	}
	vector<int>res3 = daor(x, y);
	for(int i = 0; i < m; i++)
	{
		x[i] = a[i] + a[m + i] + a[m * 2 + i];
		y[i] = b[i] + b[m + i] + b[m * 2 + i];
	}
	vector<int>res4 = daor(x, y);
	for(int i = 0; i < m; i++)
		res4[i] -= res1[i] + res2[i] + res3[i];
	vector<int>c(n);
	for(int i = 0; i < m; i++)
	{
		c[i] = res1[i];
		c[m + i] = res2[i] + res3[i];
		c[2 * m + i] = res4[i];
	}
	return c;
}
signed main()
{
	int k, n;
	scanf("%lld", &k);
	n = 1;
	for(int i = 1; i <= k; i++)
		n *= 3;
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