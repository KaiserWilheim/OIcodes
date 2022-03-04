#include<bits/stdc++.h> 
using namespace std;
const int N = 36;
int n, equ, var, d[N], x[N];
typedef int matrix[N][N];
matrix a, g;
bool vis[N];
char s[3][N];
void read()
{
	scanf("%d", &n);
	scanf("%s%s%s", s[0], s[1], s[2]);
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 2; j++)
			a[n - i][s[j][i] - 'A' + 1]++;
		a[n - i][s[2][i] - 'A' + 1]--;
	}
	for(i = 1; i <= n; i++)
		g[i][i] = n, g[i][i - 1] = -1;
	g[1][0] = 0;
	equ = var = n;
}
int gcd(int a, int b)
{
	int t;
	while(b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
void gauss()
{
	int i, j, row, col, mxr, lcm;
	for(row = col = 1; row <= equ && col <= var; row++, col++)
	{
		mxr = row;
		for(i = row + 1; i <= equ; i++)
			if(abs(a[i][col]) > abs(a[mxr][col]))
				mxr = i;
		if(mxr != row)
			swap(a[row], a[mxr]), swap(g[row], g[mxr]);
		if(!a[row][col])
		{
			row--;
			continue;
		}
		for(i = 1; i <= equ; i++)
			if(i != row && a[i][col])
			{
				lcm = a[i][col] / gcd(a[i][col], a[row][col]) * a[row][col];
				int t1 = lcm / a[i][col], t2 = lcm / a[row][col];
				for(j = 1; j <= var; j++)
				{
					g[i][j] = t1 * g[i][j] - t2 * g[row][j];
					a[i][j] = t1 * a[i][j] - t2 * a[row][j];
				}
			}
	}
}
bool check()
{
	int i, j;
	memset(vis, 0, sizeof vis);
	for(i = 1; i <= n; i++)
	{
		x[i] = 0;
		for(j = 1; j <= n; j++)
			x[i] += g[i][j] * d[j];
		if(x[i] % a[i][i])return 0;
		if(x[i] / a[i][i] < 0)return 0;
		if(x[i] / a[i][i] >= n)return 0;
		if(vis[x[i] / a[i][i]])return 0;
		x[i] /= a[i][i];
		vis[x[i]] = 1;
	}
	return 1;
}
void print()
{
	for(int i = 1; i <= n; i++)
		printf("%d%c", x[i],(i==n?'\n':' '));
}
void dfs(int i)
{
	if(i == n)
	{
		if(check())
		{
			print();
			exit(0);
		}
		return;
	}
	d[i] = 1;
	dfs(i + 1);
	d[i] = 0;
	dfs(i + 1);
}
int main()
{
	read();
	gauss();
	dfs(1);
}
