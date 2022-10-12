#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int kpd(int a, int b)
{
	return b ? kpd(b, a % b) : a;
}
int main()
{
	scanf("%d", &n);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		if(a < 0)a = -a;
		ans = kpd(a, ans);
	}
	printf("%d\n", ans);
	return 0;
}