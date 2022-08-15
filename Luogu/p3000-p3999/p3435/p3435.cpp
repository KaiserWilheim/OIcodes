#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<int>kmp(string s)
{
	int n = (int)s.length();
	vector<int>pi(n);
	for (int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])j = pi[j - 1];
		if (s[i] == s[j])j++;
		pi[i] = j;
	}
	return pi;
}
int main()
{
	int n;
	string s;
	cin >> n >> s;
	vector<int>pi = kmp(s);
	ll ans = 0;
	for (int i = 2; i <= n; i++)
	{
		int j = i;
		while (pi[j - 1])j = pi[j - 1];
		if (pi[i - 1] != 0)pi[i - 1] = j;
		ans += i - j;
	}
	cout << ans << endl;
	return 0;
}