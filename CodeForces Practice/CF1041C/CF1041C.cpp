#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
ll m, k;
struct Data
{
	ll v;
	int id;
	Data(ll _v, int _id) { this->v = _v, this->id = _id; }
	bool operator < (const Data &a)const
	{
		return v < a.v;
	}
};
set<Data>s;
int pos[N];
int main()
{
	scanf("%d%lld%lld", &n, &m, &k);
	for(int i = 1; i <= n; i++)
	{
		ll x;
		scanf("%lld", &x);
		s.emplace(x, i);
	}
	int now = s.begin()->v, cnt = 1;
	pos[s.begin()->id] = 1;
	s.erase(s.begin());
	for(int i = 2; i <= n; i++)
	{
		Data x(now + k + 1, 0);
		set<Data>::iterator it = s.lower_bound(x);
		if(it != s.end())
		{
			pos[it->id] = cnt;
			now = it->v;
			s.erase(it);
			continue;
		}
		++cnt;
		it = s.begin();
		pos[it->id] = cnt;
		now = it->v;
		s.erase(it);
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		printf("%d ", pos[i]);
	putchar('\n');
	return 0;
}