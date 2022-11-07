#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
ll a[N], b[N];
ll ans = 0;
vector<ll>d;
set<ll>vis;
void solve(ll x)
{
	if(vis.count(x))return;
	vis.insert(x);
	d.clear();
	for(ll i = 1; i * i <= x; i++)
	{
		if(x % i != 0)continue;
		d.push_back(i);
		if(i * i != x)d.push_back(x / i);
	}
	sort(d.begin(), d.end());
	for(int i = 1; i <= n; i++)
	{
		ll g = __gcd(a[i], x);
		b[lower_bound(d.begin(), d.end(), g) - d.begin()]++;
	}
	for(auto i = d.begin(); i != d.end(); i++)
		for(auto j = next(i); j != d.end(); j++)
			if(*j % *i == 0)
				b[i - d.begin()] += b[j - d.begin()];
	for(int i = 0; i < d.size(); i++)
	{
		if(b[i] * 2 >= n)ans = max(ans, d[i]);
		b[i] = 0;
	}
}
int main()
{
	double usec;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	mt19937 rnd(time(0));
	for(int i = 1; i <= min(n, 10); i++)
	{
		int id = rnd() % n + 1;
		solve(a[id]);
	}
	printf("%lld\n", ans);
	return 0;
}