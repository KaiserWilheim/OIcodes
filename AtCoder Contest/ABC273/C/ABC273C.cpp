#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int a[N];
int tmp[N];
int cnt[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	sort(tmp + 1, tmp + 1 + n);
	m = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
	for(int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(tmp + 1, tmp + 1 + m, a[i]) - tmp;
		cnt[m - a[i]]++;
	}
	for(int i = 0; i < n; i++)
		printf("%d\n", cnt[i]);
	return 0;
}