#include<bits/stdc++.h>
using namespace std;
int is[31];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(is, 0, sizeof(is));
		int n, l;
		scanf("%d%d", &n, &l);
		for(int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			for(int j = 1; x; j++)
			{
				is[j] += x % 2;
				x /= 2;
			}
		}
		int ans = 0;
		for(int i = 1; i <= l; i++)
		{
			if((is[i] * 2) >= n)ans += (1 << (i - 1));
		}
		cout << ans << endl;
	}
	return 0;
}
