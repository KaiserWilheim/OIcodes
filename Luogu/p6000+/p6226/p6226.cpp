#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 510, M = 5010, K = N * N;
int n, m, q;
char s[N][N], op[M];
bitset<K>b, f, w, e;
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	scanf("%s", op + 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(s[i][j] == '.')b[(i - 1) * m + j] = 1;
			if(j != 1)e[(i - 1) * m + j] = 1;
			if(j != m)w[(i - 1) * m + j] = 1;
		}
	}
	f = b;
	for(int i = 1; i <= q; i++)
	{
		if(op[i] == 'N')f = (f >> m) & b;
		if(op[i] == 'S')f = (f << m) & b;
		if(op[i] == 'W')f = (f >> 1) & w & b;
		if(op[i] == 'E')f = (f << 1) & e & b;
		if(op[i] == '?')f = ((f >> m) | (f << m) | (f >> 1 & w) | (f << 1 & e)) & b;
	}
	printf("%d\n", f.count());
	return 0;
}
