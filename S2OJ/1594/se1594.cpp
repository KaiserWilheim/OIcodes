#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int kpd(int a, int b)
{
	if(a < b)swap(a, b);
	return b ? kpd(b, a % b) : a;
}
int n;
int a[N];
bool chq(int div, int ret)
{
	int g = 0;
	for(int i = 1; i <= n; i++)
	{
		if(ret > a[i])return false;
		if((a[i] - ret) % div)g = kpd(g, a[i] - ret);
		if(g && g <= ret)return false;
	}
	if(g == 1)return false;
	return true;
}
int main()
{
	scanf("%d", &n);
	if(n <= 2) { puts("1"); return 0; }
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	int minn = INT_MAX, pos = 0;
	for(int i = 3; i <= n; i++)
	{
		if(a[i] - a[i - 2] < minn)
		{
			minn = a[i] - a[i - 2];
			pos = i - 2;
		}
	}
	int lim;
	lim = a[pos + 1] - a[pos];
	for(int i = 1; i * i <= lim; i++)
	{
		if(lim % i == 0)
		{
			if(i != 1)
				if(chq(i, a[pos] % i)) { puts("1"); return 0; }
			if(i * i != lim)
				if(chq(lim / i, a[pos] % (lim / i))) { puts("1"); return 0; }
		}
	}
	lim = a[pos + 2] - a[pos + 1];
	for(int i = 1; i * i <= lim; i++)
	{
		if(lim % i == 0)
		{
			if(i != 1)
				if(chq(i, a[pos + 1] % i)) { puts("1"); return 0; }
			if(i * i != lim)
				if(chq(lim / i, a[pos + 1] % (lim / i))) { puts("1"); return 0; }
		}
	}
	lim = a[pos + 2] - a[pos];
	for(int i = 1; i * i <= lim; i++)
	{
		if(lim % i == 0)
		{
			if(i != 1)
				if(chq(i, a[pos] % i)) { puts("1"); return 0; }
			if(i * i != lim)
				if(chq(lim / i, a[pos] % (lim / i))) { puts("1"); return 0; }
		}
	}
	puts("2");
	return 0;
}