#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
const int INF = 1e9;
int n;
int f[3];
int main()
{
	scanf("%d", &n);
	int x;
	scanf("%d", &x);
	memset(f, 63, sizeof(f));
	f[x + 1] = 0;
	for(int i = 2; i <= n; i++)
	{
		scanf("%d", &x);
		if(x == -1)
		{
			f[1] = INF;
			f[2] += 2;
		}
		else if(x == 0)
		{
			f[1] = min(f[0], f[1]);
			f[0]++, f[2]++;
		}
		else
		{
			f[2] = min(f[0], min(f[1], f[2]));
			f[1] = f[0] + 1;
			f[0] += 2;
		}
	}
	int res = min(f[0], min(f[1], f[2]));
	if(res >= INF)puts("BRAK");
	else printf("%d\n", res);
	return 0;
}
