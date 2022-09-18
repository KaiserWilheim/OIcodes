#include<bits/stdc++.h>
using namespace std;
const int N = 70;
int n;
int cnt[N];
int main()
{
	ll x;
	cin >> x;
	for(int i = 0; i <= 60; i++)
	{
		if((x >> i) & 1)
			cnt[n++] = i;
	}
	for(int S = 0; S < (1 << n); S++)
	{
		ll res = 0;
		for(int i = 0; i < n; i++)
			if((S >> i) & 1)res += (1ll << cnt[i]);
		cout << res << endl;
	}
	return 0;
}