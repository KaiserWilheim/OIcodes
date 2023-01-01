#include<bits/stdc++.h>
using namespace std;
#define ll long long
set<pair<int, int>>s;
int main()
{
	ll n, m, a, b, ans = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		b %= m;
		if(b == 0)	continue;
		b = m - b;
		ans += b * a;
		s.insert(make_pair(b, a));
	}
	auto r = s.lower_bound(make_pair(m / 2, 0)), l = r;
	l--;
	ll rcnt = (*r).second, lcnt = 0;
	if(r != s.begin())
	{
		lcnt = (*l).second;
	}
	else
	{
		ll allcnt = 0;
		while(r != s.end())
		{
			allcnt += rcnt;
			r++;
			rcnt = (*r).second;
		}
		ans -= allcnt / 2 * m;
		cout << ans << endl;
		return 0;
	}
	ll costsum = 0;
	if((*r).first == m / 2)
	{
		r++;
		rcnt = 0;
		if(r != s.end())
			rcnt = (*r).second;
	}
	while(true)
	{
		if(!rcnt)
		{
			r++;
			if(r == s.end())	break;
			rcnt = (*r).second;
		}
		if(!lcnt)
		{
			if(l == s.begin())	break;
			l--;
			lcnt = (*l).second;
		}
		while((*l).first + (*r).first < m && r != s.end())
		{
			r++;
			rcnt = (*r).second;
		}
		if(r == s.end())	break;
		ll now = min(lcnt, rcnt);
		lcnt -= now; rcnt -= now;
		costsum += now;
		ans -= now * m;
	}
	ll allcnt = 0;
	r = s.lower_bound(make_pair(m / 2, 0));
	while(r != s.end())
	{
		allcnt += (*r).second;
		r++;
		rcnt = (*r).second;
	}
	ans -= (allcnt - costsum) / 2 * m;
	cout << ans << endl;
	return 0;
}
