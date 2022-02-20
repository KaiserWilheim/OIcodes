#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 400010;
struct need
{
	int x, y;
	bool operator < (const need &a) const
	{
		return (x + y) < (a.x + a.y);
	}
}order[N];
priority_queue <int, vector<int>                 > q1;
priority_queue <int, vector<int>, greater<int>   > q2;
int n, k, ans, u, v, cnt;
int ans1[N], ans2[N];
char x[2], y[2];
int t[N], tot, res, sum1, sum2;
void exchange()
{
	if(q1.top() > q2.top())
	{
		int u = q1.top(), v = q2.top();
		q1.pop(), q1.push(v);
		q2.pop(), q2.push(u);
		sum1 += v - u, sum2 -= v - u;
	}
}
void clear()
{
	while(!q1.empty()) q1.pop();
	while(!q2.empty()) q2.pop();
	sum1 = sum2 = 0;
	u = v = 0;
}
void senhan()
{
	clear();
	for(int i = 1; i <= cnt; i++)
	{
		q1.push(order[i].x), q1.push(order[i].y);
		sum1 += order[i].x + order[i].y, sum1 -= q1.top(), sum2 += q1.top();
		q2.push(q1.top()); q1.pop();
		exchange();
		ans1[i] = sum2 - sum1;
	}
}
void gohan()
{
	clear();
	for(int i = cnt; i >= 1; i--)
	{
		q1.push(order[i].x), q1.push(order[i].y);
		sum1 += order[i].x + order[i].y, sum1 -= q1.top(), sum2 += q1.top();
		q2.push(q1.top()); q1.pop();
		exchange();
		ans2[i] = sum2 - sum1;
	}
}
signed main()
{
	scanf("%lld%lld", &k, &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s%lld%s%lld", x, &u, y, &v);
		if(x[0] == y[0]) ans += abs(u - v);
		else
		{
			order[++cnt] = { u, v };
			t[++tot] = u, t[++tot] = v;
			ans++;
		}
	}
	if(k == 1)
	{
		sort(t + 1, t + 1 + tot);
		for(int i = 1; i <= tot; i++)
			ans += abs(t[tot >> 1] - t[i]);
		printf("%lld\n", ans);
	}
	else if(k == 2)
	{
		sum1 = 0, sum2 = 0;
		sort(order + 1, order + 1 + cnt);
		senhan();
		gohan();
		res = 1e18;
		for(int i = 0; i <= cnt; i++)
			res = min(res, ans1[i] + ans2[i + 1]);
		printf("%lld\n", ans + res);
	}
	else
	{
		puts("orz");
	}
	return 0;
}
