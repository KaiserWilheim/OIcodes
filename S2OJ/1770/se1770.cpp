#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
int n, m, a, b, c;
void solve()
{
	scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
	int x = min(n, m / c);
	int ans = 0;
	for(int i = 0; i <= x; i++)
	{
		int tmp = 0;
		if(i == 0)tmp = 1 + (n - 1) / a + (m - 1) / b;
		else
		{
			tmp = tmp + 1 + (i - 1) * 2;
			if(n - i >= 1)tmp = tmp + 1 + (n - i - 1) / a;
			if(c - 1 >= b)tmp = tmp + (c - 1) / b * i;
			if(m - c * i - 1 >= 0)
			{
				tmp++;
				int q = ((c - 1) / b + 1) * b - c + 1,
					p = m - c * i - 1;
				if(p / q >= i)tmp = tmp + i, p = p - q * i;
				else tmp = tmp + p / q, p = p - p / q * q;
				tmp = tmp + p / b;
			}
		}
		ans = max(ans, tmp);
	}
	printf("%d\n", ans + 1);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
}