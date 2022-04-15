#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int a[N];
int ans1, ans2;
int main()
{
	int l, n;
	scanf("%d%d", &l, &n);
	l++;
	for(int i = 1; i <= n; i++)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		x++, y++;
		if(op == 0)
		{
			for(int i = x; i <= y; i++)
			{
				if(a[i] == -1)ans2++;
				a[i] = 1;
			}
		}
		else if(op == 1)
		{
			for(int i = x; i <= y; i++)
			{
				if(a[i] == 1)a[i] = -1;
			}
		}
	}
	for(int i = 1; i <= l; i++)
		if(a[i] == -1)ans1++;
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
