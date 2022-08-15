#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
int n;
ll x;
string s;
int tt = 0;
int h[N], temp[N];
signed main()
{
	cin >> n >> x >> s;
	while(x)
	{
		temp[++tt] = x & 1;
		x >>= 1;
	}
	for(int i = 1; i <= tt; i++)h[i] = temp[tt - i + 1];
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == 'U')
		{
			tt--;
		}
		else if(s[i] == 'L')
		{
			h[++tt] = 0;
		}
		else if(s[i] == 'R')
		{
			h[++tt] = 1;
		}
	}
	ll ans = 0;
	for(int i = 1; i <= tt; i++)
	{
		ans = ans * 2 + h[i];
	}
	cout << ans << endl;
	return 0;
}
