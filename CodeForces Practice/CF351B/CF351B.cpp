#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
#define lowbit(x) (x&(-x))
int n, m;
int a[N];
int tr[N];
int ans;
void segadd(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
int segsum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = n; i >= 1; i--)
	{
		ans += segsum(a[i] - 1);
		segadd(a[i], 1);
	}
	printf("%d.000000\n", (ans * 2) - (ans & 1));
	return 0;
}