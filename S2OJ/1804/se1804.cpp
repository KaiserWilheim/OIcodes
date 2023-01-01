#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m;
int s[N], t[N];
int pre[N];
vector<int>kmp(vector<int>s, int m)
{
	int n = s.size();
	vector<int>pi(n);
	for(int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while(j > 0 && (s[i] != s[j] && (~s[j] || s[i] - 1 < j)))j = pi[j - 1];
		if(s[i] == s[j] || (s[j] == -1 && s[i] - 1 >= j))j++;
		pi[i] = min(j, m);
	}
	return pi;
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &s[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &t[i]);
	memset(pre, -1, sizeof(pre));
	vector<int>s1, s2;
	for(int i = 1; i <= m; i++)
	{
		int x = i - pre[t[i]];
		if(x >= m || pre[t[i]] == -1)x = -1;
		s2.push_back(x);
		pre[t[i]] = i;
	}
	memset(pre, -1, sizeof(pre));
	for(int i = 1; i <= n; i++)
	{
		int x = i - pre[s[i]];
		if(x >= m || pre[s[i]] == -1)x = -1;
		s1.push_back(x);
		pre[s[i]] = i;
	}
	vector<int>s3;
	for(int i = 1; i <= m; i++)
		s3.push_back(s2[i - 1]);
	s3.push_back(1919810);
	for(int i = 1; i <= n; i++)
		s3.push_back(s1[i - 1]);
	vector<int>pi = kmp(s3, m);
	vector<int>res;
	for(int i = m + m; i <= n + m; i++)
		if(pi[i] == m)res.push_back(i - m - m + 1);
	printf("%d\n", res.size());
	for(int i = 0; i < res.size(); i++)
		printf("%d ", res[i]);
	putchar('\n');
}
int main()
{
	int T, C;
	scanf("%d%d", &T, &C);
	while(T--)
	{
		solve();
	}
	return 0;
}