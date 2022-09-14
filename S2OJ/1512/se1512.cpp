#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int n, a, b;
int h[N], v[N];
int id[N];
struct TreeArray
{
	int tr[N];
	int lowbit(int x) { return x & -x; }
	void segadd(int x, int c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr[i] += c;
	}
	int segsum(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
	int qwert(int l, int r)
	{
		return segsum(r) - segsum(l - 1);
	}
};
TreeArray sum, cnt;
int ans[N];
signed main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++)
	{
		cin >> h[i];
		v[i] = h[i];
	}
	sort(v + 1, v + 1 + n);
	for(int i = 1; i <= n; i++)
		id[i] = lower_bound(v + 1, v + 1 + n, h[i]) - v;
	for(int i = 1; i <= n; i++)
	{
		cnt.segadd(id[i], 1);
		sum.segadd(id[i], h[i]);
		int k = -i * b;
		int l = 1, r = n;
		while(l < r)
		{
			int mid = (l + r) >> 1;
			if(k + cnt.qwert(1, mid) * (a + b) < 0)l = mid + 1;
			else r = mid;
		}
		ans[i] = (cnt.qwert(1, l) * v[l] - sum.qwert(1, l)) * a + (sum.qwert(l, n) - cnt.qwert(l, n) * v[l]) * b;
	}
	for(int i = 1; i <= n; i++)
		cout << ans[i] << endl;
	return 0;
}