#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 15;
const int M = 524300;
int n, m;
int val[N][N][2];
int dp[N][M], d[N][M], t[N][M];
struct Step
{
	int st, nw;
};
int main()
{
	scanf("%d%d", &n, &m);
	t[m][(1 << (n - 1)) - 1] = (n * m + 1) % 2;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &val[i][j][0]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &val[i][j][1]);
	queue<Step>q;
	q.push({ m,(1 << (n - 1)) - 1 });
	do
	{
		int st = q.front().st, nw = q.front().nw;
		int px = 1, py = st;
		int ns = nw >> 1;
		if((nw & 1) == 0 && st != 1)
		{
			d[st - 1][ns]++;
			t[st - 1][ns] = t[st][nw] ^ 1;
			if(d[st - 1][ns] == 1)
				q.push({ st - 1,ns });
		}
		for(int i = 0, p = nw; py > 0 && px < n; p >>= 1, i++)
		{
			if((p & 1) == 1 && ((p >> 1) & 1) == 0)
			{
				ns = (py == 1) ? (nw ^ (1 << i)) : (nw ^ (3 << i));
				d[st][ns]++;
				t[st][ns] = t[st][nw] ^ 1;
				if(d[st][ns] == 1)
					q.push({ st,ns });
			}
			if(p & 1)px++;
			else py--;
		}
		dp[st][nw] = t[st][nw] ? -0x3f3f3f3f : 0x3f3f3f3f;
		q.pop();
	} while(!q.empty());
	dp[m][(1 << (n - 1)) - 1] = 0;
	q.push({ m,(1 << (n - 1)) - 1 });
	do
	{
		int st = q.front().st, nw = q.front().nw;
		int px = 1, py = st;
		int ns = nw >> 1;
		if(t[st][nw])
		{
			if((nw & 1) == 0 && st != 1)
			{
				d[st - 1][ns]--;
				if(d[st - 1][ns] == 0)
					q.push({ st - 1,ns });
				dp[st - 1][ns] = min(dp[st - 1][ns], dp[st][nw] - val[1][st][1]);
			}
			for(int i = 0, p = nw; py > 0 && px < n; p >>= 1, i++)
			{
				if((p & 1) == 1 && ((p >> 1) & 1) == 0)
				{
					ns = (py == 1) ? (nw ^ (1 << i)) : (nw ^ 3 << i);
					d[st][ns]--;
					if(d[st][ns] == 0)
						q.push({ st,ns });
					dp[st][ns] = min(dp[st][ns], dp[st][nw] - val[px + 1][py][1]);
				}
				if(p & 1)px++;
				else py--;
			}
		}
		else
		{
			if((nw & 1) == 0 && st != 1)
			{
				d[st - 1][ns]--;
				if(d[st - 1][ns] == 0)
					q.push({ st - 1,ns });
				dp[st - 1][ns] = max(dp[st - 1][ns], dp[st][nw] + val[1][st][0]);
			}
			for(int i = 0, p = nw; py > 0 && px < n; p >>= 1, i++)
			{
				if((p & 1) == 1 && ((p >> 1) & 1) == 0)
				{
					ns = (py == 1) ? (nw ^ (1 << i)) : (nw ^ 3 << i);
					d[st][ns]--;
					if(d[st][ns] == 0)
						q.push({ st,ns });
					dp[st][ns] = max(dp[st][ns], dp[st][nw] + val[px + 1][py][0]);
				}
				if(p & 1)px++;
				else py--;
			}
		}
		q.pop();
	} while(!q.empty());
	printf("%d\n", dp[1][0] + val[1][1][0]);
	return 0;
}
