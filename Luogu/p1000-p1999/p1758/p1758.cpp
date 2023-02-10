#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 510, M = 1010;
const int mod = 1024523;
int n, m;
char s[N], t[N];
int f[2][N][N];
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int main()
{
	scanf("%d%d%s%s", &n, &m, s + 1, t + 1);
	f[0][0][0] = 1;
	int tmp;
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = 0; k <= n; k++)
			{
				tmp = f[i & 1][j][k];
				if(i + j - k > m || i + j - k < 0)continue;
				if(s[i + 1] == s[k + 1])f[(i + 1) & 1][j][k + 1] = add(f[(i + 1) & 1][j][k + 1], tmp);
				if(t[j + 1] == t[i + j - k + 1])f[i & 1][j + 1][k] = add(f[i & 1][j + 1][k], tmp);
				if(s[i + 1] == t[i + j - k + 1])f[(i + 1) & 1][j][k] = add(f[(i + 1) & 1][j][k], tmp);
				if(t[j + 1] == s[k + 1])f[i & 1][j + 1][k + 1] = add(f[i & 1][j + 1][k + 1], tmp);
				f[i & 1][j][k] = 0;
			}
		}
	}
	printf("%d\n", tmp);
	return 0;
}
