#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
int n, m;
string s;
int main()
{
	cin >> n;
	cin >> s;
	if(n % 2 == 0)
	{
		puts("NOT POSSIBLE");
		return 0;
	}
	m = n / 2;
	int cans = 0;
	int cnt = 0;
	int i, j;
	for(i = 0, j = m; i < m && j < n; i++, j++)
	{
		while(j < n && s[i] != s[j])
		{
			j++;
			cnt++;
		}
	}
	cnt += m - i;
	if(cnt <= 1)cans += 1;
	cnt = 0;
	for(i = 0, j = m + 1; i <= m && j < n; i++, j++)
	{
		while(i <= m && s[i] != s[j])
		{
			i++;
			cnt++;
		}
	}
	cnt += n - j;
	if(cnt <= 1)cans += 2;
	if(cans == 0)puts("NOT POSSIBLE");
	else if(cans == 1)cout << s.substr(0, m) << endl;
	else if(cans == 2)cout << s.substr(m + 1, m) << endl;
	else if(cans == 3)
	{
		string tmpa = s.substr(0, m),
			tmpb = s.substr(m + 1, m);
		if(tmpa == tmpb)cout << tmpa << endl;
		else puts("NOT UNIQUE");
	}
	return 0;
}