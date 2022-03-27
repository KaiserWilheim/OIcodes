#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
int h[100];
int idx;
int main()
{
	ll n, k;
	cin >> n >> k;
	k = k ^ (k >> 1);
	while(k)
	{
		h[++idx] = k & 1;
		k >>= 1;
	}
	for(int i = n; i >= 1; i--)
		printf("%d", h[i]);
	putchar('\n');
	return 0;
}
