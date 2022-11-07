#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = 1028;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c - 48), c = getchar();
	return x;
}
int n, q;
int a[N];
ll b[N];
int ne[N][M];
ll ans;
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i <= n; i++)
		b[i] = read();
	for(int i = n; i; i--)
	{
		for(int j = 0; j < 1 << 10; j++)
		{
			if((j | a[i]) == j) ne[i][j] = i;
			else ne[i][j] = ne[i + 1][j];
		}
	}
	q = read();
	while(q--)
	{
		int l = read(), r = read(), x = read();
		ll sum = 0;
		l = ne[l][x];
		while(l && l <= r)
		{
			sum += b[l];
			x -= a[l];
			l = ne[l][x];
		}
		ans ^= sum;
	}
	cout << ans << endl;
	return 0;
}