#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010, M = N << 1;
const int MAXN = -1e9;
int n;
int f[N][N];
struct Node
{
	int a, b;
	bool operator < (const Node &rhs)const
	{
		return a > rhs.a;
	}
};
Node w[3010];
int ans = INT_MIN;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &w[i].a, &w[i].b);
	sort(w + 1, w + 1 + n);
	for(int i = 0; i <= n; i++)
		f[0][i] = MAXN, f[i][n + 1] = MAXN;
	f[0][1] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			f[i][j] = max(f[i - 1][j], f[i - 1][max(j - w[i].a, 0) + 1] + w[i].b);
		}
	}
	for(int i = 0; i <= n; i++)
		ans = max(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}
