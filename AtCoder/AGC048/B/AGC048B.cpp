#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N], b[N];
int c[N], d[N];
ll sum = 0;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(i & 1)c[(i >> 1) + 1] = a[i];
		else d[(i >> 1)] = a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		if(i & 1)c[(i >> 1) + 1] -= b[i];
		else d[(i >> 1)] -= b[i];
		sum += b[i];
	}
	sort(c + 1, c + 1 + (n >> 1));
	sort(d + 1, d + 1 + (n >> 1));
	for(int i = (n >> 1); i >= 1; i--)
	{
		if(c[i] + d[i] <= 0)break;
		sum += c[i] + d[i];
	}
	printf("%lld\n", sum);
	return 0;
}
