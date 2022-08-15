#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 30010;
int n, mq;
int sg[N];
int cnt[310] = { 0 };
void get(int x, int p)
{
	int y = x, res = 0;
	for(int i = 1; i <= mq; i++)
	{
		if(y % p != 0)break;
		y /= p;
		res ^= sg[y];
		if(res < 310)cnt[res] = x;
	}
}
void get_sg(int x)
{
	for(int i = 2; x % i == 0; i *= 2)
		get(x, i);
	for(int i = 3; x % i == 0; i *= 3)
		get(x, i);
	for(int i = 0;; i++)
	{
		if(cnt[i] != x)
		{
			sg[x] = i;
			return;
		}
	}
}
void solve()
{
	scanf("%d%d", &n, &mq);
	for(int i = 1; i <= n; i++)get_sg(i);
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		if(!x)res ^= sg[i];
	}
	if(!res)puts("lose");
	else puts("win");
	return;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(cnt, 0, sizeof(cnt));
		solve();
	}
	return 0;
}
