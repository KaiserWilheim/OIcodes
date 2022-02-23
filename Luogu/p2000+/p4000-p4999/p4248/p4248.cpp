#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
int n, a[N], c[N];
char str[N];
ll ans;
struct SAM
{
	int cnt, last, ch[N][26], fa[N], l[N], size[N];
	inline void ins(int c)
	{
		int p = last, np = ++cnt;
		l[last = np] = l[p] + 1;
		for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
		if(!p) fa[np] = 1;
		else
		{
			int q = ch[p][c];
			if(l[q] == l[p] + 1) fa[np] = q;
			else
			{
				int nq = ++cnt;
				l[nq] = l[p] + 1;
				memcpy(ch[nq], ch[q], sizeof(ch[q]));
				fa[nq] = fa[q]; fa[q] = fa[np] = nq;
				for(; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
			}
		}
		size[np] = 1;
	}
	inline void calc()
	{
		for(int i = 1; i <= cnt; i++) c[l[i]] ++;
		for(int i = 1; i <= cnt; i++) c[i] += c[i - 1];
		for(int i = 1; i <= cnt; i++) a[c[l[i]] --] = i;
		for(int i = cnt; i; i--)
		{
			int p = a[i];
			size[fa[p]] += size[p];
			ans += ( ll )(l[p] - l[fa[p]]) * size[p] * (n - size[p]);
		}
	}
} sam;
int main()
{
	scanf("%s", str);
	n = strlen(str);
	sam.last = sam.cnt = 1;
	for(int i = 0; i < n; i++)sam.ins(str[i] - 'a');
	sam.calc();
	printf("%lld", ans);
}
