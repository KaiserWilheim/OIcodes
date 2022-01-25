#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
#define ll long long;
struct Mark
{
	ll val;
	int tp;
	friend bool operator < (Mark a, Mark b)
	{
		return (a.val == b.val) ? a.tp > b.tp:a.val > b.val;
	}
};
priority_queue <Mark> pq;
int n, k;
ll a[N], b[N];
ll nk;
inline ll jud(int &cnt)
{
	cnt = 0; ll ret = 0;
	for(int i = 1; i <= n; i++)
	{
		pq.push((Mark) { a[i], 1 });
		Mark nw = pq.top();
		ll del = b[i] + nw.val + nk;
		if(del < 0)
		{
			ret += del;
			cnt += nw.tp;
			pq.pop();
			pq.push((Mark) { -nk - b[i], 0 });
		}
	}
	priority_queue <Mark> emp;
	swap(emp, pq);
	return ret;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
	int tmp;
	for(int i = 1; i <= n; i++)scanf("%lld", &b[i]);
	ll l = -(1ll << 31), r = 0;
	while(l < r)
	{
		ll mid = (l + r - 1) / 2;
		nk = mid;
		int cnt = 0;
		jud(cnt);
		if(cnt <= k)r = mid;
		else l = mid + 1;
	}
	nk = l;
	printf("%lld", jud(tmp) - ( ll )l * k);
	return 0;
}
