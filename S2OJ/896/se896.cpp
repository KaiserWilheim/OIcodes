#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
const ll mod = 1e9 + 7;
int n, m;
struct Node
{
	int x, y;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		return lhs.x < rhs.x;
	}
};
Node a[N];
ll f[N][2];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + 1 + n);
	f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i][0] = f[i][1] = 1;
		for(int j = i - 1; j >= 1; j--)
		{
			if(a[j].y > a[i].y)f[j][1] = (f[j][1] + f[i][0]) % mod;
			else f[i][0] = (f[i][0] + f[j][1]) % mod;
		}
	}
	ll res = 0;
	for(int i = 1; i <= n; i++)
		res = (res + f[i][0] + f[i][1] - 1) % mod;
	printf("%lld\n", res);
	return 0;
}