#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int l = 0, r = s.size() - 1;
	while(s[l] == 'a')l++;
	while(s[r] == 'a')r--;
	if(l + r >= s.size())
	{
		puts("No");
		return 0;
	}
	while(l <= r)
	{
		if(s[l] != s[r])
		{
			puts("No");
			return 0;
		}
		l++;
		r--;
	}
	puts("Yes");
	return 0;
}
