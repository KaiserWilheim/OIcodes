#include<bits/stdc++.h>
using namespace std;
const int N = 400010;
int n, k;
int a[N];
struct node
{
	int v, k;
	bool operator < (const node &rhs) const
	{
		return v == rhs.v ? k < rhs.k : v < rhs.v;
	}
}b[N];
int minp[N];
int res[N];

int main()
{
	scanf("%d%d", &n, &k);
	memset(minp, 0x3f, sizeof(minp));
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	for(int i = k + 1; i <= n; i++)b[i] = { a[i],i };
	sort(b + 1, b + 1 + n);
	for(int i = n; i >= k + 1; i--)minp[i] = min(minp[i + 1], b[i].k);
	for(int i = k + 1; i <= n; i++)res[i] = b[i].v;
	int ans = 0x3f3f3f3f;
	res[n + 1] = ans;
	for(int i = 1; i <= k; i++)
	{
		int now = upper_bound(res + 1, res + 2 + n, a[i]) - res;
		if(now > n)continue;
		ans = min(ans, minp[now] - i);
	}
	printf("%d\n", (ans == 0x3f3f3f3f ? -1 : ans));
	return 0;
}
