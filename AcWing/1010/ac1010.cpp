#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010;
int n;
int a[N];
int f[N];
int q[N];
int main()
{
	int x;
	while(scanf("%d", &x) == 1)a[++n] = x;
	int maxn = 0;
	for(int i = n; i >= 1; i--)
	{
		if(maxn == 0 || a[i] >= f[maxn])
		{
			maxn++;
			f[maxn] = a[i];
			continue;
		}
		int k = upper_bound(f + 1, f + 1 + maxn, a[i]) - f;
		f[k] = a[i];
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		if(cnt == 0)
		{
			cnt++;
			q[cnt] = a[i];
			continue;
		}
		int k = lower_bound(q + 1, q + 1 + cnt, a[i]) - q;
		if(q[k] < a[i])q[++cnt] = a[i];
		else q[k] = a[i];
	}
	printf("%d\n%d\n", maxn, cnt);
	return 0;
}
