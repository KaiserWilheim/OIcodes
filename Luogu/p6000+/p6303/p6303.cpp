#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
char s[N], t[N];
deque<pair<int, int>>x, y;
stack<pair<int, int>>tmp1, tmp2;
void swapq(int f, int g, vector<pair<int, int>> &ans)
{
	int res1 = 0, res2 = 0;
	while(f--)
		tmp1.push(x.front()), res1 += x.front().first, x.pop_front();
	while(g--)
		tmp2.push(y.front()), res2 += y.front().first, y.pop_front();
	ans.emplace_back(res1, res2);
	if(!x.empty() && !tmp2.empty() && x.front().second == tmp2.top().second)
	{
		pair<int, int>tx = x.front(), ty = tmp2.top();
		x.pop_front(), tmp2.pop();
		pair<int, int>res = make_pair(tx.first + ty.first, tx.second);
		x.push_front(res);
	}
	if(!y.empty() && !tmp1.empty() && y.front().second == tmp1.top().second)
	{
		pair<int, int>tx = y.front(), ty = tmp1.top();
		y.pop_front(), tmp1.pop();
		pair<int, int>res = make_pair(tx.first + ty.first, tx.second);
		y.push_front(res);
	}
	while(!tmp2.empty())x.push_front(tmp2.top()), tmp2.pop();
	while(!tmp1.empty())y.push_front(tmp1.top()), tmp1.pop();
}
void work(vector<pair<int, int>> &ans)
{
	while(x.size() > 1 || y.size() > 1)
	{
		if(x.empty() || y.empty())
		{
			if(x.empty())swapq(0, 1, ans);
			else swapq(1, 0, ans);
		}
		else if(abs((int)x.size() - (int)y.size()) < 2 || (x.size() <= 3 && y.size() <= 3))
		{
			swapq(1, 1, ans);
		}
		else
		{
			if(x.size() > y.size())swapq(3, 1, ans);
			else swapq(1, 3, ans);
		}
	}
}
int main()
{
	cin >> s + 1 >> t + 1;
	n = strlen(s + 1), m = strlen(t + 1);
	int pre = 1;
	for(int i = 2; i <= n; i++)
	{
		if(s[i] != s[i - 1])
		{
			x.emplace_back(i - pre, s[i - 1]);
			pre = i;
		}
	}
	x.emplace_back(n - pre + 1, s[n]);
	pre = 1;
	for(int i = 2; i <= m; i++)
	{
		if(t[i] != t[i - 1])
		{
			y.emplace_back(i - pre, t[i - 1]);
			pre = i;
		}
	}
	y.emplace_back(m - pre + 1, t[m]);
	if(x.size() == 1 && y.size() == 1)
	{
		puts("0");
		return 0;
	}
	vector<pair<int, int>>ans;
	if(x.front().second != y.front().second)work(ans);
	else
	{
		vector<pair<int, int>>ans1, ans2;
		deque<pair<int, int>>tmp1 = x, tmp2 = y;
		swapq(0, 1, ans1);
		work(ans1);
		x = tmp1, y = tmp2;
		swapq(1, 0, ans2);
		work(ans2);
		if(ans1.size() < ans2.size())ans = ans1;
		else ans = ans2;
	}
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d\n", i.first, i.second);
	return 0;
}