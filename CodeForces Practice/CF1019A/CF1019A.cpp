#include<bits/stdc++.h>
using namespace std;
const int N = 3010;
struct person
{
	int p, c;
	friend bool operator < (person a, person b)
	{
		return a.c < b.c;
	}
}s[N];
int n, m;
long long ans;
int p[N];
bool v[N];
int main()
{
	int i, j;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++)
	{
		scanf("%d%d", &s[i].p, &s[i].c);
		p[s[i].p]++;
	}
	int mv = p[1];
	sort(s + 1, s + n + 1);
	int t[N];
	long long cnt, vote;
	ans = 0x7fffffffffffffff;
	for(i = mv; i <= n; i++)
	{
		memset(v, 0, sizeof(v));
		memset(t, 0, sizeof(t));
		cnt = vote = 0;
		for(j = 1; j <= n; j++)
		{
			if(s[j].p == 1)
			{
				vote++, v[j] = 1;
				continue;
			}
			if(p[s[j].p] - t[s[j].p] >= i)
			{
				cnt += s[j].c, v[j] = 1, t[s[j].p]++, vote++;
			}
		}
		j = 1;
		while(vote < i)
		{
			if(!v[j])cnt += s[j].c, vote++;
			j++;
		}
		ans = min(ans, cnt);
	}
	cout << ans << endl;
	return 0;
}
