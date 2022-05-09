#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010;
const int INF = 0x3f3f3f3f;
int a[N], b[N];
int n;
int f[N][N];

int work()
{
	for(int i = 1; i <= n; i++)b[i] = a[i];
	sort(b + 1, b + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		int minn = INF;
		for(int j = 1; j <= n; j++)
		{
			minn = min(minn, f[i - 1][j]);
			f[i][j] = minn + abs(a[i] - b[j]);
		}
	}
	int res = INF;
	for(int i = 1; i <= n; i++)
		res = min(res, f[n][i]);
	return res;
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> a[i];
	int res = work();
	reverse(a + 1, a + 1 + n);
	res = min(res, work());
	cout << res << endl;
	return 0;
}
