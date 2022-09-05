#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m, l;
int a[N], b[N];
int main()
{
	scanf("%d%d", &n, &l);
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &a[i]);
		m += a[i];
	}
	b[0] = m, a[n] = m;
	for (int i = 0; i < n; i++)
	{
		for (int j = min(i + l, n); j >= i + 1; j--)
		{
			if (b[j] < a[j])
			{
				if (b[j] + b[i] <= a[j])
				{
					b[j] += b[i];
					b[i] = 0;
					break;
				}
				else
				{
					b[i] -= a[j] - b[j];
					b[j] = a[j];
				}
			}
		}
	}
	printf("%d\n", b[n]);
	return 0;
}