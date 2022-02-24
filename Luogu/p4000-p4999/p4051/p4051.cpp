#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
using namespace std;
int n, m, x[N], y[N], c[N], sa[N], p, t;
char s[N];

int main()
{
	int i, k;
	scanf("%s", s);
	t = strlen(s); m = 300; n = t << 1;
	for(i = t; i < n; i++) s[i] = s[i - t];
	for(i = 0; i < n; i++) c[x[i] = s[i]]++;
	for(i = 1; i < m; i++) c[i] += c[i - 1];
	for(i = 0; i < n; i++) sa[--c[x[i]]] = i;
	for(k = 1; k <= n; k <<= 1)
	{
		p = 0;
		for(i = n - k; i < n; i++) y[p++] = i;
		for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
		for(i = 0; i < m; i++) c[i] = 0;
		for(i = 0; i < n; i++) c[x[y[i]]]++;
		for(i = 1; i < m; i++) c[i] += c[i - 1];
		for(i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
		swap(x, y); p = 1; x[sa[0]] = 0;
		for(i = 1; i < n; i++)
			x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
		if(p >= n) break;
		m = p;
	}
	for(i = 0; i < n; i++) if(sa[i] < t) printf("%c", s[(sa[i] + t - 1)]);
	return 0;
}
