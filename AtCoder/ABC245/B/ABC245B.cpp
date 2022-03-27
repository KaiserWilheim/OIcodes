#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
int vis[N];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		vis[x] = true;
	}
	int ans;
	for(int i = 0; i <= N; i++)
	{
		if(vis[i] == 0)
		{
			ans = i;
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
