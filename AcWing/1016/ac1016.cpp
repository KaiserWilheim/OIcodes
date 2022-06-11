#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010;
int n;
int a[N];
int f[N];
int main()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		f[i] = a[i];
		for(int j = 1; j < i; j++)
			if(a[i] > a[j])
				f[i] = max(f[i], f[j] + a[i]);
		maxn = max(maxn, f[i]);
	}
	printf("%d\n", maxn);
	return 0;
}
