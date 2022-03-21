#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1001000;
int T;
ll a[N], b[N];
struct SuffixArray
{
	char S[N]; int n;
	int cnt[N], sa[N], rk[N], height[N];
	int st[N][25], lg2[N];
	struct node
	{
		int id, x, y;
	}aa[N], bb[N];

	inline void buildsa()
	{
		n = strlen(S + 1);
		memset(cnt, 0, sizeof(cnt));
		memset(height, 0, sizeof(height));
		memset(sa, 0, sizeof(sa));
		memset(rk, 0, sizeof(rk));
		for(int i = 1; i <= n; i++) aa[i] = bb[i] = { 0,0,0 };
		for(int i = 1; i <= n; i++) cnt[S[i]] = 1;
		for(int i = 1; i <= 256; i++) cnt[i] += cnt[i - 1];
		for(int i = 1; i <= n; i++) rk[i] = cnt[S[i]];
		for(int L = 1; L < n; L *= 2)
		{
			for(int i = 1; i <= n; i++) aa[i] = { i,rk[i],rk[i + L] };
			for(int i = 1; i <= n; i++) cnt[i] = 0;
			for(int i = 1; i <= n; i++) cnt[aa[i].y]++;
			for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for(int i = n; i >= 1; i--) bb[cnt[aa[i].y]--] = aa[i];
			for(int i = 1; i <= n; i++) cnt[i] = 0;
			for(int i = 1; i <= n; i++) cnt[aa[i].x]++;
			for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for(int i = n; i >= 1; i--) aa[cnt[bb[i].x]--] = bb[i];
			for(int i = 1; i <= n; i++)
				if((aa[i].x == aa[i - 1].x) && (aa[i].y == aa[i - 1].y))
					rk[aa[i].id] = rk[aa[i - 1].id];
				else rk[aa[i].id] = rk[aa[i - 1].id] + 1;
		} 
		for(int i = 1; i <= n; i++) sa[rk[i]] = i; int k = 0;
		for(int i = 1; i <= n; i++)
		{
			if(k) k--;
			int j = sa[rk[i] - 1];
			while((i + k <= n) && (j + k <= n) && (S[i + k] == S[j + k])) k++;
			height[rk[i]] = k;
		}
	}

	inline void buildst()
	{
		lg2[0] = -1; for(int i = 1; i < N; i++) lg2[i] = lg2[i / 2] + 1; lg2[0] = 0;
		for(int i = 1; i <= n; i++) st[i][0] = height[i];
		for(int j = 1; (1 << j) <= n; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}

	inline int Lcp(int l, int r)
	{
		l = rk[l], r = rk[r];
		if(l > r) swap(l, r); l++;
		int k = lg2[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
}SA[2];

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%s", SA[0].S + 1);
		int n = strlen(SA[0].S + 1);
		for(int i = 1; i <= n; i++) a[i] = b[i] = 0;
		for(int i = 1; i <= n; i++)
			SA[1].S[i] = SA[0].S[n - i + 1];
		SA[0].buildsa(), SA[1].buildsa();
		SA[0].buildst(), SA[1].buildst();

		for(int Len = 1; Len <= n / 2; Len++)
		{
			for(int i = Len; i <= n; i += Len)
			{
				int l = i, r = i + Len;
				int L = n - (r - 1) + 1, R = n - (l - 1) + 1;
				int lcp = SA[0].Lcp(l, r); lcp = min(lcp, Len);
				int lcs = SA[1].Lcp(L, R); lcs = min(lcs, Len - 1);
				if(lcp + lcs >= Len)
				{
					b[i - lcs]++, b[i - lcs + (lcp + lcs - Len + 1)]--;
					a[r + lcp - (lcp + lcs - Len + 1)]++, a[r + lcp]--;
				}
			}
		} for(int i = 1; i <= n; i++) a[i] += a[i - 1], b[i] += b[i - 1];
		ll ans = 0; for(int i = 1; i < n; i++) ans += a[i] * b[i + 1];

		printf("%lld\n", ans);
	}
	return 0;
}
