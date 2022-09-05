#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010;
int n;
int v[N], c[N];
int f[N];
int ans = INT32_MIN;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++)
		for(int j = n; j >= v[i]; j--)
			f[j] = max(f[j], f[j - v[i]] + c[i]);
	for(int i = 1; i <= n; i++)
		ans = max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}