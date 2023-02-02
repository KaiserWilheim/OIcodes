#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010, M = 510;
const int INF = 1e9;
int n, m, k;
int S;
int a[N];
int num[N];
vector<int>pos[N];
int id[N], w[N];
int big[N], tt;
int cnt[M][M];
int vis[N], val[N];
int sum, res;
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	S = sqrt(n) + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		num[a[i]]++;
		pos[a[i]].push_back(i);
		if(a[i] == a[i - 1])w[a[i]]++;
	}
	for(int i = 1; i <= k; i++)
	{
		if(num[i] > S)
		{
			big[++tt] = i;
			id[i] = tt;
		}
	}
	for(int i = 1; i <= tt; i++)
	{
		for(int j : pos[big[i]])
		{
			if(id[a[j - 1]])cnt[i][id[a[j - 1]]]++;
			if(id[a[j + 1]])cnt[i][id[a[j + 1]]]++;
		}
	}
	while(m--)
	{
		int x;
		scanf("%d", &x);
		if(id[x])
		{
			int type = (vis[x] == 1 ? -1 : 1);
			for(int i = 1; i <= tt; i++)
			{
				if(i == id[x])continue;
				if(vis[big[i]])res += cnt[id[x]][i] * type;
			}
			vis[x] ^= 1;
			sum += num[x] * type;
			res += (w[x] + val[x]) * type;
		}
		else
		{
			int type = (vis[x] == 1 ? -1 : 1);
			for(int j : pos[x])
			{
				if(a[j - 1] != a[j])res += vis[a[j - 1]] * type;
				else res += type;
				if(a[j + 1] != a[j])res += vis[a[j + 1]] * type;
				if(id[a[j - 1]] && a[j - 1] != a[j])val[a[j - 1]] += type;
				if(id[a[j + 1]] && a[j + 1] != a[j])val[a[j + 1]] += type;
			}
			vis[x] ^= 1;
			sum += num[x] * type;
		}
		printf("%d\n", sum - res);
	}
	return 0;
}
