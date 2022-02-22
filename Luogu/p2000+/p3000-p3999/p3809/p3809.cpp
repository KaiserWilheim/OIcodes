#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
char s[N];
int n, w, sa[N], rk[N << 1], oldrk[N << 1];

int main()
{
	int i, p;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
	for(w = 1; w < n; w <<= 1)
	{
		sort(sa + 1, sa + n + 1, [](int x, int y) {
			return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y]; });
		memcpy(oldrk, rk, sizeof(rk));
		for(p = 0, i = 1; i <= n; ++i)
		{
			if(oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])rk[sa[i]] = p;
			else rk[sa[i]] = ++p;
		}
	}
	for(i = 1; i <= n; ++i) printf("%d ", sa[i]);
	return 0;
}
