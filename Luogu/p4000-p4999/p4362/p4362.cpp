#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
template<typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-')f = -1; c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
int n, m;
vector< pair<int, int> >e[N];
int f[N][N][2], tmp[N][2];
int tot, k;
void dfs(int p, int fa)
{
	f[p][0][0] = f[p][1][1] = 0;
	for(auto i : e[p])
	{
		int q = i.first, w = i.second;
		if(q == fa) continue;
		dfs(q, p);
		memcpy(tmp, f[p], sizeof(f[p]));
		memset(f[p], 63, sizeof(f[p]));
		for(int j = 0; j <= k; ++j)
		{
			for(int t = 0; t <= j; ++t)
			{
				f[p][j][0] = min(f[p][j][0], min(f[q][t][0] + tmp[j - t][0] + (m == 2) * w, f[q][t][1] + tmp[j - t][0]));
				f[p][j][1] = min(f[p][j][1], min(f[q][t][1] + tmp[j - t][1] + w, f[q][t][0] + tmp[j - t][1]));
			}
		}
	}
}
int main()
{
	memset(f, 63, sizeof(f));
	n = read<int>(), m = read<int>(), k = read<int>();
	for(int i = 1; i < n; i++)
	{
		int p = read<int>(), q = read<int>(), w = read<int>();
		e[p].push_back(make_pair(q, w));
		e[q].push_back(make_pair(p, w));
	}
	if(n - k < m - 1)
	{
		puts("-1");
		return 0;
	}
	dfs(1, 0);
	printf("%d\n", f[1][k][1]);
	return 0;
}
