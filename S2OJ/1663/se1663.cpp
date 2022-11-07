#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll mod = 998244853;
int n;
int w[10] = { 0,0,1,7,4,2,0,8,10 };
void solve()
{
	int n;
	scanf("%d", &n);
	if(n <= 7)
	{
		printf("%d\n", w[n]);
		return;
	}
	int k = n / 7, r = n % 7;
	if(r == 1)r = 8, k--;
	ll res = 0;
	if(r == 6)res = 68, r = 0, k--;
	if(r == 4 && k >= 1)res = 20, r = 0, k--;
	if(r == 3 && k >= 2)res = 200, r = 0, k -= 2;
	if(r == 3 && k == 1)res = 22, r = 0, k = 0;
	res += w[r];
	int a1, a2, a3, a4, a5;
	a1 = k % 10, k /= 10;
	a2 = k % 10, k /= 10;
	a3 = k % 10, k /= 10;
	a4 = k % 10, k /= 10;
	a5 = k % 10, k /= 10;
	for(int i = 1; i <= a1; i++)
		res = (res * 10 + 8) % mod;
	for(int i = 1; i <= a2; i++)
		res = (res * 17551470 + 902930064) % mod;
	for(int i = 1; i <= a3; i++)
		res = (res * 677980272 + 491733035) % mod;
	for(int i = 1; i <= a4; i++)
		res = (res * 240953035 + 546928759) % mod;
	for(int i = 1; i <= a5; i++)
		res = (res * 632268170 + 672932245) % mod;
	printf("%lld\n", res);
	return;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}