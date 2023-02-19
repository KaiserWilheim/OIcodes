#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, k;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		if(k == 1)
		{
			puts("No");
			continue;
		}
		if(n > m)swap(n, m);
		int g = gcd(n, m);
		n /= g, m /= g;
		puts((m > 2 && (m - 2) / n + 1 >= k) ? "No" : "Yes");
	}
	return 0;
}
