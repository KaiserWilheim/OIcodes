#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<int>manachar(string s)
{
	int n = s.size();
	vector<int>res(n);
	for(int i = 0, l = 0, r = -1; i < n; i++)
	{
		int k = (i > r) ? 1 : min(res[l + r - i], r - i + 1);
		while((i - k >= 0) && (i + k < n) && (s[i - k] == s[i + k]))k++;
		res[i] = k--;
		if(i + k > r)
		{
			l = i - k;
			r = i + k;
		}
	}
	return res;
}
int main()
{
	string s;
	cin >> s;
	string s1;
	s1.push_back('#');
	for(int i = 0; i < s.size(); i++)
	{
		s1.push_back(s[i]);
		s1.push_back('#');
	}
	vector<int>d = manachar(s1);
	int maxn = 0;
	for(int i : d)
		maxn = max(maxn, i - 1);
	printf("%d\n", maxn);
	return 0;
}
