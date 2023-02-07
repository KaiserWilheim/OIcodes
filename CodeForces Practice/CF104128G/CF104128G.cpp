#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = 800010;
int n;
int a[N];
int cnt;
int p, q;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	p = q = 1;
	bool flag = true;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == 1)p++, q++;
		else if(a[i] == 0)
		{
			if(q > 1)q--, cnt++;
			else p++, q++;
		}
		else if(a[i] == -1)
		{
			if(q > 1)q--;
			else
			{
				if(!cnt)
				{
					flag = false;
					break;
				}
				else
				{
					cnt--, p++, q++;
				}
			}
		}
	}
	if(!flag)
	{
		puts("-1");
		return;
	}
	int g = gcd(p, q);
	p /= g, q /= g;
	printf("%d %d\n", p, q);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		cnt = 0;
		solve();
	}
	return 0;
}
