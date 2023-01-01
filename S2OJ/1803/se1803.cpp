#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 30000010, M = N << 1;
int n, m;
ll s, b, c, d;
int a[N];
int main()
{
	scanf("%d%lld%lld%lld%lld", &n, &s, &b, &c, &d);
	for(int i = 1; i <= n; i++)
	{
		a[i] = i;
		s = (s * b + c) % d;
		swap(a[i], a[s % i + 1]);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans = max(ans, i - a[i]);
	printf("%d\n", ans);
	return 0;
}