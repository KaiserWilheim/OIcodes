#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n;
char s[N];
int cnt[26], tot;
void solve()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		cnt[s[i] - 'a']++;
	for(int i = 0; i < 26; i++)
		if(cnt[i])tot++;
	int flag = -1;
	for(int i = 0; i < 26; i++)
	{
		if(cnt[i] == 1)
		{
			flag = i;
			break;
		}
	}
	if(flag != -1)
	{
		string res;
		res.push_back('a' + flag);
		cnt[flag]--;
		for(int i = 0; i < 26; i++)
			while(cnt[i]--)
				res.push_back('a' + i);
		cout << res << endl;
	}
	else if(tot == 1)
	{
		printf("%s\n", s + 1);
	}
	else
	{
		string res;
		vector<int>v;
		for(int i = 0; i < 26; i++)
			if(cnt[i])
				v.push_back(i);
		if(n - cnt[v[0]] >= cnt[v[0]] - 2)
		{
			res.push_back('a' + v[0]);
			res.push_back('a' + v[0]);
			cnt[v[0]] -= 2;
			for(int i = v[1]; i < 26; i++)
			{
				while(cnt[i]--)
				{
					res.push_back('a' + i);
					if(cnt[v[0]])
					{
						res.push_back('a' + v[0]);
						cnt[v[0]]--;
					}
				}
			}
		}
		else if(tot == 2)
		{
			res.push_back('a' + v[0]);
			cnt[v[0]]--;
			while(cnt[v[1]]--)
				res.push_back('a' + v[1]);
			while(cnt[v[0]]--)
				res.push_back('a' + v[0]);
		}
		else
		{
			res.push_back('a' + v[0]);
			cnt[v[0]]--;
			res.push_back('a' + v[1]);
			cnt[v[1]]--;
			while(cnt[v[0]]--)
				res.push_back('a' + v[0]);
			res.push_back('a' + v[2]);
			cnt[v[2]]--;
			for(int i = v[1]; i < 26; i++)
				while(cnt[i]--)
					res.push_back('a' + i);
		}
		cout << res << endl;
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		tot = 0;
		for(int i = 0; i < 26; i++)
			cnt[i] = 0;
		solve();
	}
	return 0;
}
