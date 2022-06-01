#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
int a[N], tr[N];
int n, m;
int lowbit(int a)
{
	return a & -a;
}
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
	{
		tr[i] += c;
	}
	return;
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
	{
		res += tr[i];
	}
	return res;
}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		add(i, a[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		cin >> op >> x >> y;
		if(op == 1)
		{
			a[x] += y;
			add(x, y);
		}
		else
		{
			int res = sum(y) - sum(x - 1);
			cout << res << endl;
		}
	}
	return 0;
}
