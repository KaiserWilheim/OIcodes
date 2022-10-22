#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int a[N];
int b[N];
inline bool calc(int tl, int tr)
{
	if(tl > tr)return false;
	ll res = 0;
	for(int i = n, l = 1, r = 1; i; i--)
	{
		while(l <= n && b[i] + b[l] < tl)l++;
		while(r <= n && b[i] + b[r] <= tr)r++;
		res += r - l - (l <= i && i < r);
	}
	return (res >> 1) & 1;
}
inline bool solve(int k)
{
	for(int i = 1; i <= n; i++)
		b[i] = a[i] & ((1 << (k + 1)) - 1);
	sort(b + 1, b + 1 + n);
	return calc((1 << k), ((1 << (k + 1)) - 1)) ^ calc((3 << k), ((1 << (k + 2)) - 2));
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	int ans = 0;
	for(int i = 0; i < 26; i++)
		ans |= (solve(i) << i);
	printf("%d\n", ans);
	return 0;
}