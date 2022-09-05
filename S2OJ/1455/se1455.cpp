#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, k;
int vis[N << 1], pre[N << 1], ans[N];
int main()
{
	scanf("%d%d", &n, &k);
	int hh = N, tt = N;
	for(int i = N - n - 1; i <= N; i++)
		pre[i] = i - 1;
	int tot = 0;
	int cnt = 0, x;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if(x)
		{
			if(++tt > k && vis[tt - k])tot--;
			if(cnt)
			{
				while(--cnt)
				{
					tot += (hh > tt - k);
					vis[hh] = 1;
					hh = pre[hh];
				}
				vis[tt] = 1;
				tot++;
			}
			else
			{
				pre[tt] = hh;
				hh = tt;
			}
			ans[i - tot] = 1;
		}
		else ++cnt;
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}