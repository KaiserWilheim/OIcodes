#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 400010;
int t[N];
int c[N];
int n, m;
int a[N], b[N];
void build(int rt, int l, int r)
{
	if(l == r)
	{
		t[rt] = b[l];
		return;
	}
	int mid = l + r >> 1;
	build(rt * 2, l, mid);
	build(rt * 2 + 1, mid + 1, r);
	if(a[mid + 1] - a[mid] > 1 || c[rt * 2] || c[rt * 2 + 1])
		c[rt] = 1;
	t[rt] = max(t[rt * 2], t[rt * 2 + 1]);
}
int segsum(int rt, int l, int r, int x, int y)
{
	if(x <= l && y >= r)
		return t[rt];
	int mid = l + r >> 1;
	int ans = 0;
	if(x <= mid)
		ans = max(ans, segsum(rt * 2, l, mid, x, y));
	if(y > mid)
		ans = max(ans, segsum(rt * 2 + 1, mid + 1, r, x, y));
	return ans;
}
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	build(1, 1, n);
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		int xx, yy;
		cin >> xx >> yy;
		if(xx >= yy)
		{
			puts("false");
			continue;
		}
		int x = lower_bound(a + 1, a + 1 + n, xx) - a;
		int y = lower_bound(a + 1, a + 1 + n, yy) - a;
		int mm = 0;
		if(a[x] != xx)x--;
		if(x + 1 <= y - 1)mm = segsum(1, 1, n, x + 1, y - 1);
		if((a[y] == yy && mm >= b[y]) || (a[x] == xx && mm >= b[x]) || (a[y] == yy && a[x] == xx && b[x] < b[y]))
			puts("false");
		else if(y - x != a[y] - a[x] || a[x] != xx || a[y] != yy)
			puts("maybe");
		else
			puts("true");
	}
	return 0;
}
