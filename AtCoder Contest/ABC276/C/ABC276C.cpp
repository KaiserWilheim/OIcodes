#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N];
int b[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int l = n;
	for(int i = n - 1; i >= 1; i--)
	{
		if(a[i] > a[i + 1])
		{
			l = i;
			break;
		}
	}
	int r = n;
	for(int i = l + 1; i <= n; i++)
	{
		if(a[i] > a[l])
		{
			r = i - 1;
			break;
		}
	}
	for(int i = 1; i < l; i++)
		b[i] = a[i];
	b[l] = a[r];
	for(int i = n, j = l + 1; j <= n; i--, j++)
		b[j] = a[i];
	b[n - (r - l) + 1] = a[l];
	for(int i = 1; i <= n; i++)
		printf("%d ", b[i]);
	putchar('\n');
	return 0;
}
