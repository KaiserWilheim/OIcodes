#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, R, B;
int cntr, cntb;
char s[N];
bool isValid()
{
	if(R != 0 && B != 0)
	{
		bool flag = true;
		if(cntr / R != cntb / B)flag = false;
		if(cntr % R != 0 || cntb % B != 0)flag = false;
		return flag;
	}
	else if(R == 0)
	{
		bool flag = true;
		if(cntr != 0)flag = false;
		if(cntb % B != 0)flag = false;
		return flag;
	}
	else if(B == 0)
	{
		bool flag = true;
		if(cntb != 0)flag = false;
		if(cntr % R != 0)flag = false;
		return flag;
	}
}
vector<pair<int, int>>sta;
vector<vector<int>>ans;
int main()
{
	scanf("%d%d%d", &n, &R, &B);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
	{
		cntr += s[i] == 'R';
		cntb += s[i] == 'B';
	}
	if(!isValid())
	{
		puts("NO");
		return 0;
	}
	sta.emplace_back(0, 0);
	for(int i = 1; i <= n; i++)
	{
		sta.emplace_back(i, sta.back().second + (s[i] == 'R'));
		if(sta.size() > R + B && sta.back().second - sta[sta.size() - R - B - 1].second == R)
		{
			vector<int>res;
			for(int i = 1; i <= R + B; i++)
				res.push_back(sta[sta.size() - i].first);
			sta.erase(sta.end() - R - B, sta.end());
			ans.push_back(res);
		}
	}
	reverse(ans.begin(), ans.end());
	puts("YES");
	int S = n / (R + B);
	printf("%d\n", S);
	for(int i = 0; i < S; i++)
	{
		for(auto j : ans[i])
			printf("%d ", j);
		putchar('\n');
	}
	return 0;
}
