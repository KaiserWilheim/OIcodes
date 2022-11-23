#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int a[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == 1)
		{
			if(sum < m)sum = min(sum + 2, m);
		}
		else if(a[i] == 2)
		{
			if(sum > m - 2)
			{
				puts("No");
				return 0;
			}
			else sum = min(sum + 3, m);
		}
	}
	puts("Yes");
	return 0;
}
