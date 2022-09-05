#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) { if (c == '-') { f = -1; }c = getchar(); }
	while (isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x * f;
}
int n, c, k;
ld a[100];
bool chq(ld x)
{
	ll res = 0, num = c;
	for (int i = 1; i <= n; i++)
	{
		ll need = floor(a[i] / x) + 0.00001;
		if (!num && need >= 1) res++;
		else if (num > need - 1) num -= need - 1, res += need;
		else res += num + 1, num = 0;
	}
	return res >= k;
}
int main()
{
	n = read(), c = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = (ld)read();
	sort(a + 1, a + 1 + n, greater<int>());
	ld l = 0, r = 1e9;
	for (int i = 1; i <= 1000; i++)
	{
		ld mid = (l + r) / (ld)2.0;
		if (chq(mid)) l = mid;
		else r = mid;
	}
	printf("%.10Lf\n", l);
	return 0;
}