#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
string s;
int ans = 0;
int main()
{
	cin >> n >> s;
	if(n % 2 == 0)
	{
		puts("NOT POSSIBLE");
		return 0;
	}
	string t;
	t = s.substr(0, n / 2);
	int fail;
	fail = 0;
	int i, j;
	for(i = n / 2, j = 0; i < n; i++)
	{
		if(s[i] != t[j])fail++;
		else j++;
	}
	fail += n / 2 - j;
	if(fail == 1)ans++;
	t = s.substr(n / 2 + 1, n / 2);
	fail = 0;
	for(i = 0, j = 0; i <= n / 2; i++)
	{
		if(s[i] != t[j])fail++;
		else j++;
	}
	fail += n / 2 - j;
	if(fail == 1)ans += 2;
	if(ans == 0)puts("NOT POSSIBLE");
	else if(ans == 3)
	{
		if(s.substr(0, n / 2) == s.substr(n / 2 + 1, n / 2))cout << s.substr(0, n / 2);
		else puts("NOT UNIQUE");
	}
	else
	{
		if(ans == 1)cout << s.substr(0, n / 2);
		else cout << s.substr(n / 2 + 1, n / 2);
	}
	return 0;
}