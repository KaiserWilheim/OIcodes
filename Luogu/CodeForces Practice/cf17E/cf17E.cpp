#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4000005;
const int mod = 51123987;
inline void inc(int &a, int b) { a += b; if(a >= mod) a -= mod; }
inline void dec(int &a, int b) { a -= b; if(a < 0) a += mod; }
inline int mul(int a, int b) { return 1ll * a * b % mod; }
int n, m, ans;
char s[N], t[N];
int r[N], st[N], ed[N];
int main()
{
	cin >> n;
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
		t[++m] = '#', t[++m] = s[i];
	t[++m] = '#';
	r[1] = 1;
	int mr = 1, pos = 1;
	for(int i = 2; i <= m; i++)
	{
		r[i] = min(mr - i + 1, r[pos + pos - i]);
		while(i - r[i] > 0 && t[i + r[i]] == t[i - r[i]]) r[i] ++;
		if(i + r[i] - 1 > mr) mr = i + r[i] - 1, pos = i;
		st[i - r[i] + 1] ++; st[i + 1] --;
		ed[i] ++; ed[i + r[i]] --;
		inc(ans, r[i] / 2);
	}
	int sum = 0;
	ans = 1ll * ans * (ans - 1) / 2 % mod;
	for(int i = 1; i <= m; i++)
	{
		st[i] += st[i - 1];
		ed[i] += ed[i - 1];
		if(t[i] != '#')
		{
			dec(ans, mul(st[i], sum));
			inc(sum, ed[i]);
		}
	}
	cout << ans << endl;
	return 0;
}
