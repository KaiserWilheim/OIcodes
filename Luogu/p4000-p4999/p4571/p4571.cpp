#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n, k;
int a[N];
map<int, int>f;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		for(int j = 1; j * j <= a[i]; j++)
		{
			if(a[i] % j != 0)continue;
			f[j]++;
			if(j * j != a[i])f[a[i] / j]++;
		}
	}
	int ans = 0;
	for(auto i : f)
	{
		if(i.second >= k)ans = max(ans, i.first);
	}
	printf("%d\n", ans);
	return 0;
}