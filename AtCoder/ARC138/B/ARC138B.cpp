#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int n;
int a[N];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	if(a[1] == 1)
	{
		puts("No");
		return 0;
	}
	int idx = 0, cntr = 0, cnta = 0;
	for(int i = 2; i <= n; i++)
		if(a[i] == a[i - 1])
		{
			idx = i;
			break;
		}
	if(idx == 0)
	{
		puts("Yes");
		return 0;
	}
	for(int i = idx + 1; i <= n; i++)
		if(a[i] != a[i - 1])
			cntr++;
	for(int i = idx - 1; i > 0; i--)
		if(a[i] != a[i + 1])
			cnta++;
	if(cnta >= cntr)puts("Yes");
	else puts("No");
	return 0;
}
