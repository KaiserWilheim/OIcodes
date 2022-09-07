#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 310, M = 500010;
int n, m;
int s;
int c[N][N];
int f[M];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> s;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> c[i][j];
	for(int i = 2; i <= m; i++)
	{
		int maxn = -1;
		memset(f, 0, sizeof(f));
		for(int j = 1; j <= n; j++)
		{
			for(int k = c[j][i - 1]; k <= s; k++)
			{
				f[k] = max(f[k], f[k - c[j][i - 1]] + c[j][i] - c[j][i - 1]);
				maxn = max(maxn, f[k]);
			}
		}
		s += maxn;
	}
	cout << s << endl;
	return 0;
}