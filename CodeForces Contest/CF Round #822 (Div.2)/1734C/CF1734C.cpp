#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n;
bool vis[N];
vector<int>v[N];
int sta[N];
void solve()
{
	scanf("%d", &n);
	string s;
	cin >> s;
	for(int i = 0; i < n; i++)
		vis[i + 1] = (s[i] == '0');
	bool flag = true;
	for(int i = 1; i <= n; i++)
	{
		sta[i] = i;
		if(vis[i] == true)flag = false;
	}
	if(flag)
	{
		puts("0");
		return;
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			sta[i] = 0;
			continue;
		}
		int minn = i;
		for(int j : v[i])
		{
			if(sta[j] == i)
			{
				minn = min(minn, j);
				sta[j] += j;
			}
		}
		ans += minn;
	}
	printf("%lld\n", ans);
}
int main()
{
	for(int i = 1; i <= 1e6; i++)
		for(int j = i; j <= 1e6; j += i)
			v[j].push_back(i);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}