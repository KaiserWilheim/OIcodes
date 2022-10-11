#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define ll long long
const int N = 100010;
int n;
ll a[N];
unordered_set<ll>zfy;
void solve()
{
	zfy.clear();
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	zfy.insert(a[1]);
	for(int i = 2; i <= n; i++)
	{
		if(zfy.count(a[i]))
		{
			puts("Yes");
			return;
		}
		unordered_set<ll>tmp;
		tmp.insert(a[i]);
		for(auto j : zfy)
		{
			if(zfy.count(j + a[i]))
			{
				puts("Yes");
				return;
			}
			else tmp.insert(j + a[i]);
		}
		for(auto j : tmp)
			zfy.insert(j);
	}
	puts("No");
	return;
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}