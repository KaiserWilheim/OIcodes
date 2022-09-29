#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
char s[N];
int f[N], h[N];
int ne[N];
int main()
{
	cin >> s + 1;
	n = strlen(s + 1);
	ne[0] = -1;
	for(int i = 2, j = 0; i <= n; i++)
	{
		while(j != -1 && s[i] != s[j + 1]) j = ne[j];
		ne[i] = ++j;
	}
	f[1] = 1;
	h[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i] = i;
		if(h[f[ne[i]]] >= i - ne[i])f[i] = f[ne[i]];
		h[f[i]] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}