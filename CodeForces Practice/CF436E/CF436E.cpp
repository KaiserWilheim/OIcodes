#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = N << 1;
int n, m;
int st[N];
ll a[M];
bool vis[M];
ll sum;
priority_queue<pair<ll, int> >q, t;
void dump(priority_queue<pair<ll, int> > &q)
{
	while(!q.empty() && vis[q.top().second])q.pop();
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
	{
		scanf("%lld%lld", &a[i], &a[i + n]);
		a[i + n] -= a[i];
		q.push(make_pair(-a[i], i));
		t.push(make_pair(-a[i] - a[i + n], i));
	}
	while(m--)
	{
		dump(q), dump(t);
		int i = q.top().second;
		q.pop();
		dump(q);
		if(m && !t.empty() && a[i] - q.top().first >= -t.top().first)
		{
			q.push(make_pair(-a[i], i));
			i = t.top().second;
			t.pop();
		}
		if(i < n)q.push(make_pair(-a[i + n], i + n));
		sum += a[i];
		st[i % n]++;
		vis[i] = true;
	}
	printf("%lld\n", sum);
	for(int i = 0; i < n; i++)
		printf("%d", st[i]);
	puts("");
	return 0;
}
