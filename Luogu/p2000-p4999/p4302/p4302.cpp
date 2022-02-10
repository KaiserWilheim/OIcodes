#include <bits/stdc++.h>
using namespace std;
char s[110];
int n, m[110], f[110][110];
bool check(char s[], int n, int len)
{
	for(int i = len; i < n; i++)
		if(s[i] != s[i % len])
			return false;
	return true;
}
void init()
{
	for(int i = 1; i <= 9; i++)m[i] = 1;
	for(int i = 10; i <= 99; i++)m[i] = 2;
	m[100] = 3;
	memset(f, 0x3f, sizeof(f));
	for(int i = 0; i < n; i++)f[i][i] = 1;
}
int main()
{
	scanf("%s", s);
	n = strlen(s);
	init();
	for(int l = 2; l <= n; l++)
	{
		for(int i = 0, j = i + l - 1; j < n; i++, j++)
		{
			for(int k = i; k < j; k++)
				f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
			for(int k = i; k < j; k++)
			{
				int len = k - i + 1;
				if(l % len != 0)continue;
				if(check(s + i, l, len))f[i][j] = min(f[i][j], f[i][k] + 2 + m[l / len]);
			}
		}
	}
	printf("%d", f[0][n - 1]);
	return 0;
}
