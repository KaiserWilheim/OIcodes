#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 510;
int n, m;
char s[N];
void get(ll &wr, ll &wi)
{
	ll fr = 1, fi = 1;
	wr = 0, wi = 0;
	n = strlen(s + 1);
	int now = 1;
	if(s[now] == '-')fr = -1, now++;
	while(s[now] >= '0' && s[now] <= '9' && now <= n)
	{
		wr = wr * 10 + (s[now] ^ 48);
		now++;
	}
	if(now == n + 1)
	{
		wr *= fr;
		return;
	}
	if(s[now] == 'i')
	{
		if(wr == 0)wr = 1;
		wi = wr * fr, wr = 0;
		return;
	}
	if(s[now] == '-')fi = -1;
	now++;
	while(s[now] >= '0' && s[now] <= '9' && now <= n)
	{
		wi = wi * 10 + (s[now] ^ 48);
		now++;
	}
	if(wi == 0)wi = 1;
	wr *= fr, wi *= fi;
	return;
}
int main()
{
	cin >> s + 1;
	ll wr, wi;
	get(wr, wi);
	string res;
	if(wr == 0 && wi == 0)res = "0";
	while(wr != 0 || wi != 0)
	{
		ll p, q;
		ll r = abs(wr + wi) % 2;
		res.push_back(r == 0 ? '0' : '1');
		p = (r - wr + wi) / 2;
		q = (r - wr - wi) / 2;
		wr = p, wi = q;
	}
	reverse(res.begin(), res.end());
	cout << res;
	return 0;
}