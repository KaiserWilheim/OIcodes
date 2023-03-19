#include<bits/stdc++.h>
using namespace std;
const int N = 25, M = (1 << 24) + 10;
int n;
int g[N], ans[N];
int f[M];
int ctz[M], ne[M];
#define lowbit(i) ((i)&-(i))
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		char s[N];
		scanf("%s", s);
		for(int j = 0; j < n; j++)
			g[i] |= (s[j] - '0') << j;
	}
	for(int S = 1; S < (1 << n); S++)
	{
		ctz[S] = (S & 1) ? 0 : (ctz[S >> 1] + 1);
		ne[S] = ne[S ^ lowbit(S)] | g[ctz[S]];
	}
	f[1] = 1;
	for(int S = 1; S < (1 << n); S++)
		for(int T = ne[f[S]]; T; T ^= lowbit(T))
			if(!(S & (lowbit(T))))
				f[S | lowbit(T)] |= lowbit(T);
	for(int S = 1; S < (1 << n); S++)
	{
		int k = ((1 << n) - 1) ^ S ^ 1;
		for(int T = f[S]; T; T ^= lowbit(T))
			ans[ctz[T]] |= f[k];
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			printf("%d", (ans[i] >> j) & 1);
		putchar('\n');
	}
	return 0;
}
