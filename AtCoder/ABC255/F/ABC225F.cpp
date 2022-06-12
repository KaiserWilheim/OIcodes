#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a[N], b[N], pos[N], ls[N], rs[N];
int get_root(int l1, int r1, int l2, int r2)
{
	if(l1 > r1) return 0;
	if(pos[a[l1]] < l2 || pos[a[l1]] > r2)
	{
		puts("-1");
		exit(0);
	}
	int len1 = pos[a[l1]] - l2;
	int len2 = (r2 - l2 + 1) - len1 - 1;
	ls[a[l1]] = get_root(l1 + 1, l1 + len1, l2, pos[a[l1]] - 1);
	rs[a[l1]] = get_root(l1 + len1 + 1, r1, pos[a[l1]] + 1, r2);
	return a[l1];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &b[i]);
		pos[b[i]] = i;
	}
	int x = get_root(1, n, 1, n);
	if(x != 1)
	{
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", ls[i], rs[i]);
	return 0;
}
