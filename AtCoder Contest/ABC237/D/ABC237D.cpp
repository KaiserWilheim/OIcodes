#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
struct LianBiao
{
	int v;
	int l, r;
}a[N];
int idx = 0, head = 0;
int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	a[++idx] = { 0,-1,-1 };
	head = 1;
	int now = 1;
	for(int i = 1; i <= n; i++)
	{
		if(s[i - 1] == 'L')
		{
			a[++idx] = { i,a[now].l,now };
			a[a[now].l].r = idx;
			a[now].l = idx;
			if(now == head)head = idx;
		}
		else if(s[i - 1] == 'R')
		{
			a[++idx] = { i,now,a[now].r };
			a[a[now].r].l = idx;
			a[now].r = idx;
		}
		now = idx;
	}
	for(int i = head; ~i; i = a[i].r)
	{
		printf("%d ", a[i].v);
	}
	putchar('\n');
	return 0;
}
