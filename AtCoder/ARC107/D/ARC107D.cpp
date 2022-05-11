#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
const int p = 998244353;
int n, m;
int f[N][N];
int main()
{
	scanf("%d%d", &n, &m);
	f[1][1] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = i; j >= 1; j--)
			f[i][j] = (f[i - 1][j - 1] + f[i][2 * j]) % p;
	printf("%d\n", f[n][m]);
	return 0;
}
