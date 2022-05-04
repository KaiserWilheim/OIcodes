#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
struct query
{
	int l, r, v;
}a[N], b[N];
bool cmp1(query a, query b)
{
	return a.l == b.l ? a.r < b.r : a.l < b.l;
}
bool cmp2(query a, query b)
{
	return a.r == b.r ? a.l < b.l : a.r < b.r;
}
int erfen(int l, int r, int v)
{
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(a[mid].r < v)l = mid + 1;
		else r = mid - 1;
	}
	return r;
}
int f[N];
int main()
{
	int tempn, tmpn = 0;
	scanf("%d", &tempn);
	for(int i = 1; i <= tempn; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		a[i].l = x + 1, a[i].r = tempn - y;
	}
	sort(a + 1, a + 1 + tempn, cmp1);
	for(int i = 1; i <= tempn; i++)
		if(a[i].l <= a[i].r)
			b[++tmpn] = a[i];//delete l>r
	for(int i = 1; i <= tmpn; i++)
	{
		if(i == 1 || b[i].l != b[i - 1].l || b[i].r != b[i - 1].r)a[++n] = { b[i].l,b[i].r,1 };
		else if(a[n].v < a[n].r - a[n].l + 1)a[n].v++;
	}
	sort(a + 1, a + n + 1, cmp2);
	f[1] = a[1].v;
	for(int i = 2; i <= n; i++)
	{
		int ne = erfen(1, i - 1, a[i].l);
		f[i] = max(f[i - 1], f[ne] + a[i].v);
	}
	printf("%d\n", tempn - f[n]);
	return 0;
}
