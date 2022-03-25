#include<bits/stdc++.h>
const int N = 10010;
const int maxn = 100000010;
using namespace std;
int m;
int lc[N * 40], rc[N * 40], sum[N * 80], cnt, root;
void ins(int &rt, int l, int r, int q, int v)
{
	if(!rt)rt = ++cnt;
	sum[rt] += v;
	if(l == r)return; int mid = (l + r) / 2;
	if(q <= mid)ins(lc[rt], l, mid, q, v);
	else ins(rc[rt], mid + 1, r, q, v);
}
int queryx(int rt, int l, int r, int ql, int qr)
{
	int mid = (l + r) / 2, ans = 0;
	if(ql <= l && r <= qr)return sum[rt];
	if(ql <= mid)ans += queryx(lc[rt], l, mid, ql, qr);
	if(qr > mid)ans += queryx(rc[rt], mid + 1, r, ql, qr);
	return ans;
}
int querykth(int rt, int l, int r, int k)
{
	int mid = (l + r) / 2; if(l == r)return l;
	int s = sum[lc[rt]];
	if(k <= s)return querykth(lc[rt], l, mid, k);
	else return querykth(rc[rt], mid + 1, r, k - s);
}
map<int, int> ma;
int main()
{
	scanf("%d", &m);
	while(m--)
	{
		int opt, x;
		scanf("%d%d", &opt, &x);
		if(opt == 1)
		{
			ins(root, 1, maxn * 2, x + maxn, 1), ma[x]++;
		}
		else if(opt == 2)
		{
			ins(root, 1, maxn * 2, x + maxn, -1); ma[x]--;
			if(ma[x] == 0)ma.erase(x);
		}
		else if(opt == 3)
		{
			printf("%d\n", queryx(root, 1, maxn * 2, 1, x + maxn - 1) + 1);
		}
		else if(opt == 4)
		{
			printf("%d\n", querykth(root, 1, maxn * 2, x) - maxn);
		}
		else if(opt == 5)
		{
			printf("%d\n", (--ma.lower_bound(x))->first);
		}
		else if(opt == 6)
		{
			printf("%d\n", (ma.upper_bound(x))->first);
		}
	}
	return 0;
}
