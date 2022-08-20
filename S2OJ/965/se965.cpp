#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
ll ans;
string s;
map<string, int>dic;
int main()
{
	scanf("%d", &n);
	cin >> s;
	for(int i = 0; i < (1 << n); i++)
	{
		string s1, s2;
		for(int j = 1; j <= n; j++)
			if((1 << (j - 1)) & i)s1.push_back(s[j - 1]);
		for(int j = n; j; j--)
			if(!((1 << (j - 1)) & i))s2.push_back(s[j - 1]);
		dic[s1 + "$" + s2]++;
	}
	for(int i = 0; i < (1 << n); i++)
	{
		string s1, s2;
		for(int j = n + 1; j <= n * 2; j++)
			if((1 << (j - n - 1)) & i)s1.push_back(s[j - 1]);
		for(int j = n * 2; j >= n + 1; j--)
			if(!((1 << (j - n - 1)) & i))s2.push_back(s[j - 1]);
		ans += dic[s2 + "$" + s1];
	}
	printf("%lld\n", ans / 2);
	return 0;
}