#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
struct prg
{
	int x, y;
	friend bool operator < (const prg &lhs, const prg &rhs)
	{
		return lhs.y < rhs.y;
	}
};
prg a[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + 1 + n);
	multiset<int, greater<int> >s;
	for(int i = 1; i <= m; i++)s.insert(-1);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		auto k = s.lower_bound(a[i].x);
		if(k != s.end())s.erase(k), s.insert(a[i].y), ans++;
	}
	printf("%d\n", ans);
	return 0;
}