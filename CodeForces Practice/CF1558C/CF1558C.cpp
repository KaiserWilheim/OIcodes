#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
int a[N];
int find(int x)
{
	for(int i = 1; i <= n; i++)
		if(a[i] == x)return i;
}
vector<int>ans;
void rev(int p)
{
	if(p == 1)return;
	reverse(a + 1, a + 1 + p);
	ans.push_back(p);
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		if((a[i] & 1) != (i & 1))
		{
			puts("-1");
			return;
		}
	}
	ans.clear();
	for(int i = 1; i < n; i += 2)
	{
		int l = find(i);
		rev(l);
		int r = find(i + 1);
		rev(r - 1);
		rev(r + 1);
		rev(3);
		rev(n - i + 1);
	}
	rev(n);
	printf("%d\n", ans.size());
	for(int i : ans)
		printf("%d ", i);
	putchar('\n');
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
