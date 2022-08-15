#include<bits/stdc++.h>
using namespace std;
#define ll long long
int ans = 0;
vector<int>manachar(string s)
{
	int n = s.size();
	vector<int>res(n);
	for(int i = 0, l = 0, r = -1; i < n; i++)
	{
		int k = (i > r) ? 1 : min(res[l + r - i], r - i + 1);
		while((i - k >= 0) && (i + k < n) && (s[i - k] == s[i + k]))k++;
		res[i] = k;
		if(i + k > r)
		{
			if(i & 1)
			{
				for(int j = max(r, i + 4); j < i + k; j++)
					if(!(j - i & 3) && (res[i - (j - i) / 2] > (j - i) / 2))
						ans = max(ans, j - i);
			}
			k--;
			l = i - k;
			r = i + k;
		}
	}
	return res;
}
int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	string s1;
	s1.push_back('~');
	s1.push_back('#');
	for(int i = 0; i < s.size(); i++)
	{
		s1.push_back(s[i]);
		s1.push_back('#');
	}
	vector<int>d = manachar(s1);
	printf("%d\n", ans);
	return 0;
}
