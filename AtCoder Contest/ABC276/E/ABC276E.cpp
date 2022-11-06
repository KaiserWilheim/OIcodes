#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
string s[N];
map<pair<int, int>, int>dic;
int x[5] = { 0,1,0,-1,0 }, y[5] = { 0,0,1,0,-1 };
bool chq(int i, int j)
{
	if(i < 1)return false;
	if(i > n)return false;
	if(j < 1)return false;
	if(j > m)return false;
	if(s[i][j] != '.')return false;
	return true;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		cin >> s[i];
	for(int i = 1; i <= n; i++)
		s[i] = ' ' + s[i];
	pair<int, int>st;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(s[i][j] == 'S')
			{
				st = { i,j };
				break;
			}
		}
	}
	queue<pair<int, int>>q;
	dic[st] = -1;
	for(int i = 1; i <= 4; i++)
	{
		int nx = st.first + x[i], ny = st.second + y[i];
		if(!chq(nx, ny))continue;
		dic[make_pair(nx, ny)] = i;
		q.push(make_pair(nx, ny));
	}
	while(!q.empty())
	{
		pair<int, int>now = q.front();
		q.pop();
		for(int i = 1; i <= 4; i++)
		{
			int nx = now.first + x[i], ny = now.second + y[i];
			if(!chq(nx, ny))continue;
			if(dic.count(make_pair(nx, ny)))
			{
				int col = dic[make_pair(nx, ny)];
				if(col != dic[now])
				{
					puts("Yes");
					return 0;
				}
			}
			else
			{
				dic[make_pair(nx, ny)] = dic[now];
				q.push(make_pair(nx, ny));
			}
		}
	}
	puts("No");
	return 0;
}
