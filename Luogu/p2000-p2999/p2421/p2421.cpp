#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
int n;
struct Au
{
	int p, c, l;
}s[N];
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1, y = 0;
		return a;
	}
	int g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}
bool chq(int k)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			int a = s[i].p - s[j].p,
				b = k,
				c = s[j].c - s[i].c;
			int x, y;
			int g = exgcd(a, b, x, y);
			if(c % g)continue;
			a /= g, b = abs(b / g), c /= g;
			x = (x * c % b + b) % b;
			if(x <= s[i].l && x <= s[j].l)return false;
		}
	}
	return true;
}
int main()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &s[i].c, &s[i].p, &s[i].l);
		maxn = max(maxn, s[i].c);
	}
	for(int i = maxn;; i++)
	{
		if(chq(i))
		{
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
