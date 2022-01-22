#include<bits/stdc++.h>
using namespace std;
const int N = 1000010, M = N;
int n, m;
struct node
{
	int l, r;
	int v;
}tr[(N << 2) + (M * 20)];
int root[M], idx = 0;
int a[N];
int build(int l, int r)
{
	int p = ++idx;
	if(l == r)
	{
		tr[p].v = a[r];
		return p;
	}
	int mid = (l + r) >> 1;
	tr[p].l = build(l, mid);
	tr[p].r = build(mid + 1, r);
	//tr[p].v = tr[tr[p].l].v + tr[tr[p].r].v;
	return p;
}
int change(int p, int l, int r, int loc, int val)
{
	int q = ++idx;
	tr[q] = tr[p];
	if(l == r)
	{
		tr[q].v = val;
		return q;
	}
	int mid = (l + r) >> 1;
	if(loc <= mid)tr[q].l = change(tr[p].l, l, mid, loc, val);
	else tr[q].r = change(tr[p].r, mid + 1, r, loc, val);
	//tr[q].v = tr[tr[q].l].v + tr[tr[q].r].v;
	return q;
}
int search(int p, int l, int r, int loc)
{
	if(l ==r)return tr[p].v;
	int mid = (l + r) >> 1;
	if(loc <= mid)return search(tr[p].l, l, mid, loc);
	else return search(tr[p].r, mid + 1, r, loc);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	root[1] = build(1, n);
	root[0]++;
	int op, ver, loc, val;
	while(m--)
	{
		scanf("%d%d%d", &ver, &op, &loc);
		ver++;
		if(op == 1)
		{
			scanf("%d", &val);
			root[++root[0]] = change(root[ver], 1, n, loc, val);
		}
		else if(op == 2)
		{
			printf("%d\n", search(root[ver], 1, n, loc));
			root[++root[0]] = root[ver];
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
