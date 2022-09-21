#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n, m, h;
vector<int>frn[N], rgh[N];
struct Block
{
	int x, y, z;
	Block(int _x, int _y, int _z)
	{
		x = _x, y = _y, z = _z;
	}
	bool operator < (const Block &a) const
	{
		return (x == a.x) ? (y == a.y) ? (z < a.z) : (y < a.y) : (x < a.x);
	}
};
void solveMax()
{
	vector<Block>ans;
	for(int i = 0; i < n; i++)
		for(int j : frn[i])
			for(int k : rgh[i])
				ans.emplace_back(i, j, k);
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d %d\n", i.x, i.y, i.z);
}
void solveMin()
{
	vector<Block>ans;
	for(int i = 0; i < n; i++)
	{
		if(frn[i].size() < rgh[i].size())
		{
			for(int j = 0; j < rgh[i].size(); j++)
				ans.emplace_back(i, frn[i][min((int)frn[i].size() - 1, j)], rgh[i][j]);
		}
		else if(frn[i].size() > rgh[i].size())
		{
			for(int j = 0; j < frn[i].size(); j++)
				ans.emplace_back(i, frn[i][j], rgh[i][min((int)rgh[i].size() - 1, j)]);
		}
		else
		{
			for(int j = 0; j < frn[i].size(); j++)
				ans.emplace_back(i, frn[i][j], rgh[i][j]);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(auto i : ans)
		printf("%d %d %d\n", i.x, i.y, i.z);
}
int main()
{
	scanf("%d%d%d", &n, &m, &h);
	for(int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for(int j = m; ~j; j--)
			if(s[j] == '1')frn[i].push_back(j);
	}
	for(int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for(int j = h; ~j; j--)
			if(s[j] == '1')rgh[i].push_back(j);
	}
	for(int i = 0; i < n; i++)
	{
		if(frn[i].empty() ^ rgh[i].empty())
		{
			puts("-1");
			return 0;
		}
	}
	solveMax();
	solveMin();
	return 0;
}