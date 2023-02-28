#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
string s;
void solve()
{
	scanf("%d", &n);
	bool flag = false;
	unordered_map<string, bool>bib1, bib2;
	for(int i = 1; i <= n; i++)
	{
		cin >> s;
		if(s.size() == 1)flag = true;
		if(s.size() == 2 && s[0] == s[1])flag = true;
		if(s.size() == 3 && s[0] == s[2])flag = true;
		bib1[s] = true;
		bib2[s.substr(0, s.size() - 1)] = true;
		reverse(s.begin(), s.end());
		if(bib1.count(s) || bib2.count(s))flag = true;
		if(bib1.count(s.substr(0, s.size() - 1)))flag = true;
	}
	if(flag)puts("YES");
	else puts("NO");
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
