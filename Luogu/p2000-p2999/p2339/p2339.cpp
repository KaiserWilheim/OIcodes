#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, m;
int k;
int f[N][N][2];
int ans = INT_MAX;
struct HW
{
	int x, t;
	bool operator < (const HW &a)const
	{
		return x < a.x;
	}
};
HW a[N];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)
		cin >> a[i].x >> a[i].t;
	sort(a + 1, a + 1 + n);
	memset(f, 127, sizeof(f));
	f[1][n][0] = max(a[1].x, a[1].t), f[1][n][1] = max(a[n].x, a[n].t);
	for(int i = 1; i <= n; i++)
	{
		for(int j = n; j >= i; j--)
		{
			f[i][j][0] = min(f[i][j][0], max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t));
			f[i][j][0] = min(f[i][j][0], max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t));
			f[i][j][1] = min(f[i][j][1], max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t));
			f[i][j][1] = min(f[i][j][1], max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t));
		}
	}
	for(int i = 1; i <= n; i++)
		ans = min(ans, min(f[i][i][0], f[i][i][1]) + abs(k - a[i].x));
	cout << ans << endl;
	return 0;
}