#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = N << 1;
int n;
int k[N];
bitset<N>a[N], g[N], c[2];
vector<int>e[N];
void Gauss()
{
	for(int i = 1; i <= n; i++)
	{
		if(!a[i][i])
		{
			for(int j = i + 1; j <= n; j++)
			{
				if(a[j][i])
				{
					swap(a[i], a[j]);
					break;
				}
			}
		}
		for(int j = i + 1; j <= n; j++)
			if(a[j][i])a[j] ^= a[i];
	}
	for(int i = n; i >= 1; i--)
		for(int j = i + 1; j <= n; j++)
			if(a[i][j])a[i][n + 1] = a[i][n + 1] ^ a[j][n + 1];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &k[i]);
		for(int j = 1; j <= k[i]; j++)
		{
			int x;
			scanf("%d", &x);
			a[i][x] = g[i][x] = 1;
		}
		if(k[i] & 1)a[i][i] = a[i][n + 1] = 1;
	}
	Gauss();
	for(int i = 1; i <= n; i++)
		c[a[i][n + 1]][i] = 1;
	bool flag = false;
	for(int i = 1; i <= n; i++)
		if((g[i] & c[a[i][n + 1]]).count() & 1)flag = true;
	if(flag)
	{
		puts("-1");
		return 0;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(a[i][n + 1])cnt++;
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if(a[i][n + 1])printf("%d ", i);
	putchar('\n');
	return 0;
}
