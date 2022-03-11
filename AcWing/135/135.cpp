#include<bits/stdc++.h>
using namespace std;
const int N = 300010;
int n, m;
int a[N], q[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] += a[i - 1];
	}
	int hh = 0, tt = 0;
	int res = -1e9;
	for(int i = 1; i <= n; i++)
	{
		if(q[hh] < i - m)hh++;
		res = max(res, a[i] - a[q[hh]]);
		while((hh <= tt) && (a[q[tt]] >= a[i]))tt--;
		q[++tt] = i;
	}
	printf("%d\n", res);
	return 0;
}
