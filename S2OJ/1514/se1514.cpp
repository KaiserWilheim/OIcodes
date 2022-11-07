#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, k;
ll a[N], sum;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	sort(a + 1, a + 1 + n);
	int pos = n, ans = 0;
	for(int i = n; i >= 1; i--)
	{
		ll avg = sum / i;
		while(a[pos] > avg)pos--;
		ans = max(ans, i - pos);
		sum -= a[i];
	}
	printf("%d\n", ans);
	return 0;
}