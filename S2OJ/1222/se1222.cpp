#include<bits/stdc++.h>
using namespace std;
#define ll long long
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') { f = -1; }c = getchar(); }
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x * f;
}
const int N = 7.5e6 + 10, M = 1e6 + 10;
int n, m;
int a[N], b[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		a[i] = read();
		a[i] += a[i - 1];
	}
	for(int i = 1; i <= n; i++)
	{
		b[i] = read();
		b[i] += b[i - 1];
	}
	a[n + 1] = b[n + 1] = 2e9, a[0] = b[0] = -2e9;
	for(int i = 1; i <= m; i++)
	{
		int k = read();
		int l = max(0, k - n), r = min(n, k);
		while(l < r)
		{
			int mid = (l + r) >> 1;
			if(a[mid] > b[k - mid + 1])r = mid - 1;
			else if(b[k - mid] > a[mid + 1])l = mid + 1;
			else
			{
				l = r = mid;
				break;
			}
		}
		printf("%d\n", max(a[l], b[k - l]));
	}
	return 0;
}
