#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int l[N], r[N], sum[N];
int main()
{
	int n, m, last;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &l[i], &r[i]);
		l[i]--;
		for(int j = 1; j <= l[i]; j = last + 1)
		{
			last = min(l[i] / (l[i] / j), r[i] / (r[i] / j));
			if(l[i] / j < r[i] / j)
			{
				sum[j]++;
				sum[last + 1]--;
			}
		}
		sum[l[i] + 1]++;
		sum[r[i] + 1]--;
	}
	for(int i = 1; i <= m; i++)
	{
		sum[i] += sum[i - 1];
		printf("%d\n", sum[i]);
	}
	return 0;
}
