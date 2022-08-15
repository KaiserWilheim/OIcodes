#include<bits/stdc++.h>
using namespace std;
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
	cout << n - pi[n - 1] << endl;
	return 0;
}