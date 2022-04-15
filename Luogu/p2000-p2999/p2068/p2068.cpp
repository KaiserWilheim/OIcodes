#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
ll tr[N];
int n, m;
int lowbit(int a)
{
	return a & -a;
}
void add(int x, ll c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
	return;
}
ll sum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		string op;
		int x, y;
		cin >> op >> x >> y;
		if(op[0] == 'x')
			add(x, y);
		else
			cout << sum(y) - sum(x - 1) << endl;
	}
	return 0;
}
