#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n;
char s[N], t[N];
vector<pair<int, int>>ans;
bool chq()
{
	if(count(s + 1, s + 1 + n, '1') != count(t + 1, t + 1 + n, '1'))return false;
	for(int i = 1; i <= n; i++)
	{
		if(s[i] == t[i])continue;
		int cnt = 0, flag = 0;
		for(int j = i; j <= n; j++)
		{
			if(s[j] == '1')cnt++;
			if(s[j] == t[i] && cnt % 2 == 0)
			{
				flag = 1;
				ans.emplace_back(i, j);
				reverse(s + i, s + 1 + j);
				break;
			}
		}
		if(!flag)return false;
	}
	return true;
}
int main()
{
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1);
	if(!chq())puts("NO");
	else
	{
		printf("YES %d\n", ans.size());
		for(auto i : ans)
			printf("%d %d\n", i.first, i.second);
	}
	return 0;
}
