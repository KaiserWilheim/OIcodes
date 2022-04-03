#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
const ll mod = 998244353;
ll base[1510];
set<ll>h;
string s[N];
int main()
{
	int n;
	cin >> n;
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		cin >> s[i];
		maxn = max(maxn, ( int )s[i].length());
	}
	base[0] = 1;
	for(int i = 1; i <= maxn; i++)
		base[i] = (base[i - 1] * 62) % mod;
	for(int i = 1; i <= n; i++)
	{
		ll shash = 0;
		for(int j = 0; j < s[i].length(); j++)
		{
			int now;
			if(s[i][j] >= '0' && s[i][j] <= '9')now = s[i][j] - '0';
			else if(s[i][j] >= 'A' && s[i][j] <= 'Z')now = s[i][j] - 'A' + 10;
			else if(s[i][j] >= 'a' && s[i][j] <= 'z')now = s[i][j] - 'a' + 36;
			shash = (shash * 62 + now) % mod;
		}
		h.insert(shash);
	}
	cout << h.size() << endl;
	return 0;
}
