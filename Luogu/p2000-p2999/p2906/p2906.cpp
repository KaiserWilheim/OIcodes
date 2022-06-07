#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010;
template <typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
int n;
ll c;
struct Node
{
	ll x, y;
	bool operator < (const Node &a) const
	{
		return x == a.x ? y < a.y : x < a.x;
	}
}a[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int sum[N];
int main()
{
	n = read<int>(), c = read<ll>();
	for(int i = 1; i <= n; i++)
	{
		ll x = read<ll>(), y = read<ll>();
		a[i] = { x + y,x - y };
		p[i] = i;
	}
	sort(a + 1, a + 1 + n);
	set< pair<ll, int> >s;
	set< pair<ll, int> >::iterator it;
	s.insert(make_pair(a[1].y, 1));
	s.insert(make_pair((1ll << 60), 0));
	s.insert(make_pair((-1ll << 60), 0));
	for(int i = 2, l = 1; i <= n; i++)
	{
		while(a[i].x - a[l].x > c)
		{
			s.erase(make_pair(a[l].y, l));
			l++;
		}
		it = s.lower_bound(make_pair(a[i].y, 0));
		if(it->first - a[i].y <= c)
		{
			int j = it->second;
			int pa = find(i), pb = find(j);
			if(pa != pb)p[pa] = pb;
		}
		it--;
		if(a[i].y - it->first <= c)
		{
			int j = it->second;
			int pa = find(i), pb = find(j);
			if(pa != pb)p[pa] = pb;
		}
		s.insert(make_pair(a[i].y, i));
	}
	int cnt = 0, maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		cnt += (find(i) == i);
		maxn = max(maxn, ++sum[find(i)]);
	}
	printf("%d %d\n", cnt, maxn);
	return 0;
}
