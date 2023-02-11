#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, M = N << 1;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n1, n2, m, c;
int deg[N];
int main()
{
	n1 = read(), n2 = read(), m = read(), c = read();
	for(int i = 1; i <= m; i++)
	{
		int u = read(), v = read() + n1;
		deg[u]++, deg[v]++;
	}
	int res = 0;
	for(int i = 1; i <= n1 + n2; i++)res += (deg[i] % c > 0);
	printf("%d\n", res);
	return 0;
} 
