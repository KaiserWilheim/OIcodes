#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
ll k;
struct Query
{
	ll a, b;
	Query(ll _a, ll _b) { a = _a, b = _b; }
};
bool cmp1(const Query &lhs, const Query &rhs)
{
	return lhs.a < rhs.a;
}
bool cmp2(const Query &lhs, const Query &rhs)
{
	return lhs.a + lhs.b > rhs.a + rhs.b;
}
bool solve()
{
	scanf("%d%lld", &n, &k);
	k--;
	vector<Query>pos, neg;
	for(int i = 1; i <= n; i++)
	{
		ll a, b;
		scanf("%lld%lld", &a, &b);
		if(b >= a)pos.emplace_back(a, b - a);
		else neg.emplace_back(a, b - a);
	}
	sort(pos.begin(), pos.end(), cmp1);
	sort(neg.begin(), neg.end(), cmp2);
	for(auto i : pos)
	{
		if(k < i.a)return false;
		k += i.b;
	}
	for(auto i : neg)
	{
		if(k < i.a)return false;
		k += i.b;
	}
	return true;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		bool flag = solve();
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}