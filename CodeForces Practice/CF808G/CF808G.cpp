#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 800010;
int n, m;
char s[N], t[N];
int f[N], g[N];
int ne[N];
int main()
{
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	for(int i = 2, j = 0; i <= m; i++)
	{
		while(j && t[j + 1] != t[i])j = ne[j];
		if(t[j + 1] == t[i])j++;
		ne[i] = j;
	}
	for(int i = m; i <= n; i++)
	{
		f[i] = f[i - 1];
		bool flag = true;
		for(int j = 1; j <= m; j++)
			if(s[i - m + j] != t[j] && s[i - m + j] != '?')flag = false;
		if(flag)
		{
			g[i] = f[i - m] + 1;
			for(int j = ne[m]; j; j = ne[j])
				g[i] = max(g[i], g[i - (m - j)] + 1);
			f[i] = max(f[i], g[i]);
		}
	}
	printf("%d\n", f[n]);
	return 0;
}
