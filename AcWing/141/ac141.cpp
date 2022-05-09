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
int main()
{
	int n;
	string s;
	cin >> n;
	int tot = 0;
	while(n)
	{
		cin >> s;
		vector<int>pi = kmp(s);
		printf("Test case #%d\n", ++tot);
		for(int i = 0; i < n; i++)
			if(((i + 1) % (i - pi[i] + 1) == 0) && ((i + 1) != (i - pi[i] + 1)))
				printf("%d %d\n", i + 1, (i + 1) / (i - pi[i] + 1));
		putchar('\n');
		cin >> n;
	}
	return 0;
}
