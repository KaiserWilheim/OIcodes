#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010, M = 510;
const ll mod = 998244353;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
int n, m;
struct AC
{
	int s[2];
	int fail;
	int tag;
	int vis;
};
AC tr[N];
int idx = 1;
char s[N]; int len;
bool chq(int i)
{
	if(i < len - i)return false;
	int j = i + 1;
	while(i >= 1 && j <= len)
	{
		if(s[i] == s[j])return false;
		i--, j++;
	}
	return true;
}
void insert(int id)
{
	int p = 1;
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - '0';
		if(!tr[p].s[c])tr[p].s[c] = ++idx;
		p = tr[p].s[c];
		if(chq(i))tr[p].vis |= (1 << id);
	}
	tr[p].tag |= (1 << id);
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i <= 1; i++)
	{
		if(!tr[1].s[i])tr[1].s[i] = 1;
		else tr[tr[1].s[i]].fail = 1, q.push(tr[1].s[i]);
	}
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		tr[p].tag |= tr[tr[p].fail].tag;
		tr[p].vis |= tr[tr[p].fail].vis;
		for(int i = 0; i <= 1; i++)
		{
			if(!tr[p].s[i])tr[p].s[i] = tr[tr[p].fail].s[i];
			else
			{
				tr[tr[p].s[i]].fail = tr[tr[p].fail].s[i];
				q.push(tr[p].s[i]);
			}
		}
	}
}
ll f[M][N][70];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		insert(i - 1);
		reverse(s + 1, s + 1 + len);
		for(int j = 1; j <= len; j++)
			s[j] = '0' + (s[j] == '0');
		insert(i - 1);
	}
	get_fail();
	f[0][1][0] = 1;
	for(int i = 0; i < m; i++)
	{
		for(int p = 1; p <= idx; p++)
		{
			for(int S = 0; S < (1 << n); S++)
			{
				for(int k = 0; k <= 1; k++)
				{
					int v = tr[p].s[k];
					f[i + 1][v][S | tr[v].tag] = add(f[i + 1][v][S | tr[v].tag], f[i][p][S]);
				}
			}
		}
	}
	ll ans = 0;
	for(int p = 1; p <= idx; p++)
		for(int S = 0; S < (1 << n); S++)
			if((S | tr[p].vis) == (1 << n) - 1)
				ans = add(ans, f[m][p][S]);
	printf("%lld\n", ans);
	return 0;
}
