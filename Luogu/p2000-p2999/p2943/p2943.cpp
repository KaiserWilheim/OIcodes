#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 50010;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
int n, m;
ll pos[N], f[N];
int p[N], last[N], pre[N], nex[N], cnt[N];
int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
	{
		p[i] = read();
		pre[i] = last[p[i]];
		nex[last[p[i]]] = i;
		last[p[i]] = i;
		f[i] = 1e9;
		nex[i] = n + 1;
	}
	int t = sqrt(n); 
	for(int i = 1; i <= t; i++)
		pos[i] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= t; j++)
		{
			if(pre[i] < pos[j])cnt[j]++;
			if(cnt[j] > j)
			{
				cnt[j]--;
				while(nex[pos[j]] < i)pos[j]++;
				pos[j]++;
			}
			f[i] = min(f[pos[j] - 1] + j * j, f[i]);
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}
