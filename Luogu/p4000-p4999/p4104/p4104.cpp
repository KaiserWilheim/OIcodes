#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = 15;
int n, k;
ll p;
ll f[N][M];
void solve()
{
	scanf("%d%d%lld", &n, &k, &p);
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i = 1; i <= (n + 1) * k; i++)
	{
		for(int j = 1; j <= k; j++)
		{
			if(i < j)continue;
			f[i][j] = (f[i - j][j] + f[i - j][j - 1]) % p;
			if(i >= (n + 1) * 2)
				f[i][j] = (f[i][j] - f[i - (n + 1) * 2][j - 1] + p) % p;
		}
	}
	printf("%lld\n", (f[(n + 1) * k][k] + p) % p);
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
