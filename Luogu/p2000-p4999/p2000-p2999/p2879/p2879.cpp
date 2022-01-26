#include <bits/stdc++.h>
using namespace std;
int d[100005];
int n, l, h, r;
int x, y;
map<pair<int, int>, bool>book;
int main()
{
	scanf("%d%d%d%d", &n, &l, &h, &r);
	for(int i = 1; i <= r; i++)
	{
		scanf("%d%d", &x, &y);
		if(x > y)  swap(x, y);
		if(book[make_pair(x, y)])continue;
		d[x + 1]--;
		d[y]++;
		book[make_pair(x, y)] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		d[i] = d[i - 1] + d[i];
		printf("%d\n", h + d[i]);
	}
	return 0;
}

