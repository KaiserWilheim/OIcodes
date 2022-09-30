#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n;
int a[N];
void solve()
{
	int ans = INT_MAX;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i = 2; i < n; i++)
		ans = min(ans, a[i + 1] - a[i - 1]);
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}