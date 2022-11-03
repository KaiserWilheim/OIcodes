#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int a[N], sta[N], tt;
int main()
{
	scanf("%d", &n);
	while(n)
	{
		sta[++tt] = n % 10;
		n /= 10;
	}
	m = tt;
	for(int i = 1; tt; i++)
		a[i] = sta[tt--];
	int cnt = 0;
	for(int i = 1; i <= m; i++)
	{
		if(a[i] != 1 && a[i] != 4)
		{
			puts("NO");
			return 0;
		}
		if(a[i] == 4 && i == 1)
		{
			puts("NO");
			return 0;
		}
		if(a[i] == 1)cnt = 0;
		else cnt++;
		if(cnt > 2)
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
