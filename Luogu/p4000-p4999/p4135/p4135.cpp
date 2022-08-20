#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 440;
int n, m;
int c;
int S;
int lastans = 0;
int a[N];
int bl[N];
int cnt[M][N];
int f[M][M];
int main()
{
	scanf("%d%d%d", &n, &c, &m);
	S = sqrt(n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		bl[i] = i / S;
	}
	bl[n] = n;
	for(int i = 0; i <= bl[n - 1]; i++)
	{
		int t = 0;
		for(int j = i * S; j < n; j++)
		{
			cnt[i][a[j]]++;
			if(cnt[i][a[j]] & 1 && cnt[i][a[j]] > 1)t--;
			else if((cnt[i][a[j]] % 2) == 0)t++;
			if(bl[j] != bl[j + 1])f[i][bl[j]] = t;
		}
	}
	int num[N], sta[N], tt;
	memset(num, 0, sizeof(num));
	while(m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + lastans) % n;
		r = (r + lastans) % n;
		if(l > r)swap(l, r);
		int tl = bl[l], tr = bl[r];
		if(tl == tr)
		{
			tt = 0;
			for(int i = l; i <= r; i++)
			{
				num[a[i]]++;
				if(num[a[i]] == 1)sta[++tt] = a[i];
			}
			int res = 0;
			for(int i = 1; i <= tt; i++)
			{
				int k = sta[i];
				if(num[k] % 2 == 0)res++;
				num[k] = 0;
			}
			lastans = res;
			printf("%d\n", res);
		}
		else
		{
			tt = 0;
			int res = 0;
			if(tl + 1 <= tr - 1)res += f[tl + 1][tr - 1];
			for(int i = l; i < (tl + 1) * S; i++)
			{
				num[a[i]]++;
				if(num[a[i]] == 1)sta[++tt] = a[i];
			}
			for(int i = tr * S; i <= r; i++)
			{
				num[a[i]]++;
				if(num[a[i]] == 1)sta[++tt] = a[i];
			}
			for(int i = 1; i <= tt; i++)
			{
				int k = sta[i];
				if(num[k] % 2 == 1 && (cnt[tl + 1][k] - cnt[tr][k]) % 2 == 0 && (cnt[tl + 1][k] - cnt[tr][k]) > 0)res--;
				if(num[k] % 2 == 1 && (cnt[tl + 1][k] - cnt[tr][k]) % 2 == 1)res++;
				if(num[k] % 2 == 0 && (cnt[tl + 1][k] - cnt[tr][k]) == 0)res++;

				num[k] = 0;
			}
			lastans = res;
			printf("%d\n", res);
		}
	} 
	return 0;
}