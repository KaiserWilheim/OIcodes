#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
const int N = 500010;
const ll base = 13131;
int n, m;
int ne[N], prime[N];
bool vis[N];
void seive()
{
	for(int i = 2; i < N; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
			ne[i] = i;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] < N; j++)
		{
			vis[i * prime[j]] = true;
			ne[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)break;
		}
	}
}
char s[N];
ull h[N], hs[N];
int q[N], tt = 0;
bool chq(int l, int r, int k)
{
	if(h[r - k] - hs[r - k - l + 1] * h[l - 1] == h[r] - hs[r - l - k + 1] * h[l + k - 1])return true;
	else return false;
}
int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%d", &m);
	for(int i = 1; i <= n; i++)
		h[i] = h[i - 1] * base + s[i] - 'a' + 1;
	hs[0] = 1;
	for(int i = 1; i <= n; i++)
		hs[i] = hs[i - 1] * base;
	seive();
	while(m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int len = r - l + 1;
		tt = 0;
		while(len != 1)
		{
			q[++tt] = ne[len];
			len = len / ne[len];
		}
		len = r - l + 1;
		for(int i = 1; i <= tt; i++)
		{
			int k = len / q[i];
			if(chq(l, r, k))len = k;
		}
		printf("%d\n", len);
	}
	return 0;
}
