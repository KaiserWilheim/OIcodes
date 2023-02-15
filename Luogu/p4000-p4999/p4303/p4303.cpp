#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 10010;
int n;
vector<int>pos[N];
#define lowbit(i) ((i)&-(i))
int tr[N];
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] = max(tr[i], c);
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res = max(res, tr[i]);
	return res;
}
int main()
{
	scanf("%d", &n);
	n *= 5;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		pos[x].push_back(i);
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		for(int j = 4; ~j; j--)
			add(pos[x][j], sum(pos[x][j] - 1) + 1);
	}
	printf("%d\n", sum(n));
	return 0;
}
