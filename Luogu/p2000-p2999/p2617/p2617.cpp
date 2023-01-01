#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
#define lowbit(i) ((i)&-(i))
int n, m;
int a[N];
int tr[N];
int ans[N];
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
struct Node
{
	int op;
	int i, j, k;
	int id;
};
void solve(int l, int r, vector<Node> &q)
{
	vector<Node>ql, qr;
	if(q.empty())return;
	if(r - l == 1)
	{
		for(int i = 0; i < q.size(); i++)
			if(q[i].op == 1)ans[q[i].id] = l;
		return;
	}
	int mid = (l + r) >> 1;
	for(int i = 0; i < q.size(); i++)
	{
		Node tmp = q[i];
		if(tmp.op == 0)
		{
			if(tmp.k < mid)
			{
				add(tmp.i, tmp.j);
				ql.push_back(tmp);
			}
			else qr.push_back(tmp);
		}
		else
		{
			int val = sum(tmp.j) - sum(tmp.i - 1);
			if(val >= tmp.k)
			{
				ql.push_back(tmp);
			}
			else
			{
				tmp.k -= val;
				qr.push_back(tmp);
			}
		}
	}
	for(int i = 0; i < ql.size(); i++)
		if(ql[i].op == 0)
			add(ql[i].i, -ql[i].j);
	solve(l, mid, ql);
	solve(mid, r, qr);
}
int main()
{
	scanf("%d%d", &n, &m);
	vector<Node>q;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		Node tmp = { 0,i,1,a[i] };
		q.push_back(tmp);
	}
	for(int i = 0; i < m; i++)
	{
		string op;
		cin >> op;
		if(op[0] == 'C')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			Node tmp = { 0,x,-1,a[x],0 };
			q.push_back(tmp);
			a[x] = y;
			tmp = { 0,x,1,y,0 };
			q.push_back(tmp);
		}
		else
		{
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			Node tmp = { 1,l,r,k,i };
			q.push_back(tmp);
		}
	}
	for(int i = 0; i < m; i++)
		ans[i] = -1;
	solve(0, INT_MAX, q);
	for(int i = 0; i < m; i++)
		if(~ans[i])printf("%d\n", ans[i]);
	return 0;
}
