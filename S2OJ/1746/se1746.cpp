#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 600010;
int n, m;
char s[N];
map<pair<int, int>, int>dic;
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
int st[N][20], lg[N];
void build(vector<int> &a)
{
	int m = n * 2 + 1;
	for(int i = 2; i <= m; i++)
		lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= m; i++)
		st[i][0] = a[i - 1] - 1;
	for(int j = 1; j <= lg[m]; j++)
		for(int i = 1; i <= m - (1 << j) + 1; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int segmax(int l, int r)
{
	int k = lg[r - l + 1];
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
bool chq(int l, int r, int x)
{
	return segmax(l + x - 1, r - x + 1) >= x;
}
int solve(int ld, int rd)
{
	int l = 1, r = rd - ld + 1;
	int mid = 0, ans = 0;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(chq(ld * 2, rd * 2, mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	return ans;
}
int main()
{
	scanf("%s", s);
	n = strlen(s);
	string tmp;
	tmp.push_back('#');
	for(int i = 0; i < n; i++)
	{
		tmp.push_back(s[i]);
		tmp.push_back('#');
	}
	vector<int>res = manachar(tmp);
	build(res);
	scanf("%d", &m);
	for(int _i = 1; _i <= m; _i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l++, r++;
		if(l == r)
		{
			puts("1");
		}
		else if(dic.count(make_pair(l, r)))
		{
			printf("%d\n", dic[make_pair(l, r)]);
		}
		else
		{
			int ans = solve(l, r);
			printf("%d\n", ans);
			dic[make_pair(l, r)] = ans;
		}
	}
	return 0;
}
