#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int a[N];
int pos[N], top;
pair<int, int>ans[N];
int cnt;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n + 1; i++)
	{
		while(top < a[i])
			pos[++top] = i;
		while(top > a[i])
		{
			ans[++cnt] = make_pair(pos[top], i - 1);
			top--;
		}
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}