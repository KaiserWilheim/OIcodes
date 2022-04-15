#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
int tr[N];
int n, m;
int lowbit(int x)
{
	return x & -x;
}
void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
	return;
}
int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		scanf("%d", &op);
		if(op == 0)
		{
			scanf("%d%d", &x, &y);
			add(x, 1);
			add(y + 1, -1);
		}
		else if(op == 1)
		{
			scanf("%d", &x);
			printf("%d\n", sum(x) - sum(0));
		}
	}
	return 0;
}
