#include<bits/stdc++.h>
using namespace std;
string s[20];
int use[20], length = 0, n;
int canlink(string s1, string s2)
{
	for(int i = 1; i < min(s1.length(), s2.length()); i++)
	{
		int flag = 1;
		for(int j = 0; j < i; j++)
			if(s1[s1.length() - i + j] != s2[j]) flag = 0;
		if(flag) return i;
	}
	return 0;
}
void solve(string snow, int lengthnow)
{
	length = max(lengthnow, length);
	for(int i = 0; i < n; i++)
	{
		if(use[i] >= 2) continue;
		int c = canlink(snow, s[i]);
		if(c > 0)
		{
			use[i]++;
			solve(s[i], lengthnow + s[i].length() - c);
			use[i]--;
		}
	}
}
int main()
{
	cin >> n;
	for(int i = 0; i <= n; i++)
		use[i] = 0, cin >> s[i];
	solve(' ' + s[n], 1);
	cout << length;
}
