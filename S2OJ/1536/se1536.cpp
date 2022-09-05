#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20010;
int n;
string s;
string t[N];
bool vis[N];
int ans = 0;
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> s;
	int len = s.length();
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> t[i];
		if(t[i].length() == len)
		{
			vis[i] = true;
			ans++;
		}
	}
	for(int i = 0; i < len; i++)
	{
		if(s[i] == '#')continue;
		for(int j = 1; j <= n; j++)
		{
			if(!vis[j])continue;
			if(t[j][i] != s[i])
			{
				vis[j] = false;
				ans--;
			}
		}
	}
	cout << ans << endl;
	return 0;
}