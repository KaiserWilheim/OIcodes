#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010;
int n, k;
struct Volk
{
	int k, id;
	vector<int>s;
	bool operator < (const Volk &rhs)const
	{
		if(k != rhs.k)return k < rhs.k;
		return id < rhs.id;
	}
};
Volk a[N];
int lst[N];
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].k);
		a[i].s.clear();
		for(int j = 1; j <= a[i].k; j++)
		{
			int x;
			scanf("%d", &x);
			a[i].s.push_back(x);
		}
		sort(a[i].s.begin(), a[i].s.end());
		a[i].id = i;
		lst[i] = 0;
	}
	sort(a + 1, a + 1 + n);
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i <= n; i++)
	{
		map<int, int>bib;
		for(auto j : a[i].s)
		{
			bib[lst[j]]++;
			lst[j] = i;
		}
		for(auto j : bib)
		{
			if(j.first == 0)continue;
			if(a[j.first].k != j.second)
			{
				ans1 = a[j.first].id;
				ans2 = a[i].id;
				break;
			}
		}
		if(ans1 || ans2)break;
	}
	if(ans1 == 0 && ans2 == 0)puts("NO");
	else printf("YES\n%d %d\n", ans1, ans2);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
