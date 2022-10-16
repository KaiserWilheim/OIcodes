#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
char s[N];
int cnt[N][26];
int main()
{
	cin >> s + 1 >> m;
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < 26; j++)
			cnt[i][j] = cnt[i - 1][j];
		cnt[i][s[i] - 'a']++;
	}
	for(int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if(l == r)
		{
			puts("Yes");
			continue;
		}
		int tot = 0;
		for(int j = 0; j < 26; j++)
			if(cnt[r][j] > cnt[l - 1][j])tot++;
		if(tot >= 3)puts("Yes");
		else if(tot == 2 && s[l] != s[r])puts("Yes");
		else puts("No");
	}
	return 0;
}