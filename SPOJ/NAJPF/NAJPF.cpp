#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<int> kmp(string s)
{
	int n = ( int )s.length();
	vector<int> pi(n);
	for(int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while(j > 0 && s[i] != s[j]) j = pi[j - 1];
		if(s[i] == s[j]) j++;
		pi[i] = j;
	}
	return pi;
}
int ans[1000010];
int main()
{
	int T;
	string s1, s2, s3;
	cin >> T;
	while(T--)
	{
		cin >> s2 >> s1;
		int n = s1.length(), m = s2.length();
		s3 = s1 + '#' + s2;
		vector<int>pi = kmp(s3);
		ans[0] = 0;
		for(int i = n; i <= m + n; i++)
			if(pi[i] == n)
				ans[++ans[0]] = i - 2 * n + 1;
		if(ans[0])
		{
			printf("%d\n", ans[0]);
			for(int i = 1; i <= ans[0]; i++)
				printf("%d ", ans[i]);
			putchar('\n');
		}
		else
		{
			puts("Not Found");
		}
	}
	return 0;
}
