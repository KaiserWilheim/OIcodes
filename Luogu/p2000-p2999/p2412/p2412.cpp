#include <bits/stdc++.h>
using namespace std;
const int N = 1200001;
struct node
{
	int l, r;
	string maxn, out;
}tr[N];
string max(string a, string b) { return a > b ? a : b; }
string min(string a, string b) { return a < b ? a : b; }
string ans, kp, Out;
inline void pushup(int x)
{
	if(tr[x << 1].maxn > tr[x << 1 | 1].maxn)
	{
		tr[x].maxn = tr[x << 1].maxn;
		tr[x].out = tr[x << 1].out;
	}
	else
	{
		tr[x].maxn = tr[x << 1 | 1].maxn;
		tr[x].out = tr[x << 1 | 1].out;
	}
}
void build(int l, int r, int x)
{
	tr[x].l = l;
	tr[x].r = r;
	if(l == r)
	{
		cin >> tr[x].maxn; tr[x].out = tr[x].maxn;
		for(int i = 0; i < tr[x].maxn.size(); ++i)tr[x].maxn[i] = tolower(tr[x].maxn[i]);
		ans = min(ans, tr[x].maxn);
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, x << 1);
	build(mid + 1, r, x << 1 | 1);
	pushup(x);
}
int n, m;
void segmax(int l, int r, int x)
{
	if(tr[x].l >= l && tr[x].r <= r)
	{
		if(tr[x].maxn > ans)
		{
			ans = tr[x].maxn;
			Out = tr[x].out;
		}
		return;
	}
	int mid = tr[x].l + tr[x].r >> 1;
	if(l <= mid)segmax(l, r, x << 1);
	if(mid < r)segmax(l, r, x << 1 | 1);
}
int main()
{
	scanf("%d%d", &n, &m);
	build(1, n, 1);
	kp = ans;
	for(int i = 1, x, y; i <= m; ++i)
	{
		ans = kp;
		scanf("%d%d", &x, &y);
		segmax(x, y, 1);
		cout << Out << endl;
	}
	return 0;
}
