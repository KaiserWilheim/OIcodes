#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int tr[N];
int a[N], d[N];
int n, m;
int lowbit(int a)
{
	return a & -a;
}
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
	return;
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}

bool cmp(int x, int y)
{
	return a[x] == a[y] ? x > y : a[x] > a[y];
}
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		d[i] = i;
	}
	sort(d + 1, d + 1 + n, cmp);
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		add(d[i], 1);
		ans += sum(d[i] - 1);
	}
	cout << ans << endl;
	return 0;
}
