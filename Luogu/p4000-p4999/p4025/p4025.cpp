#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
ll k;
struct Query
{
	ll a, b;
	int id;
	Query(ll _a, ll _b, int _i) { a = _a, b = _b, id = _i; }
};
bool cmp1(const Query &lhs, const Query &rhs)
{
	return lhs.a < rhs.a;
}
bool cmp2(const Query &lhs, const Query &rhs)
{
	return lhs.a + lhs.b > rhs.a + rhs.b;
}
int main()
{
	scanf("%d%lld", &n, &k);
	vector<Query>pos, neg;
	for(int i = 1; i <= n; i++)
	{
		ll a, b;
		scanf("%lld%lld", &a, &b);
		if(b >= a)pos.emplace_back(a, b - a, i);
		else neg.emplace_back(a, b - a, i);
	}
	sort(pos.begin(), pos.end(), cmp1);
	sort(neg.begin(), neg.end(), cmp2);
	for(auto i : pos)
	{
		if(k <= i.a)
		{
			puts("NIE");
			return 0;
		}
		k += i.b;
	}
	for(auto i : neg)
	{
		if(k <= i.a)
		{
			puts("NIE");
			return 0;
		}
		k += i.b;
	}
	puts("TAK");
	for(auto i : pos)
		printf("%d ", i.id);
	for(auto i : neg)
		printf("%d ", i.id);
	putchar('\n');
	return 0;
}