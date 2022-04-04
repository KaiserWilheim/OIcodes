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
	string s1, s2;
	cin >> s2 >> s1;
	string s3 = s1 + "#" + s2;
	vector<int> pi1 = kmp(s3);
	int n = s1.length();
	int m = s2.length();
	for(int i = n; i < s3.length(); i++)
		if(pi1[i] == n)printf("%d\n", i - n - n + 1);
	vector<int> pi2 = kmp(s1);
	for(int i = 0; i < n; i++)printf("%d ", pi2[i]);
	putchar('\n');
	return 0;
}
