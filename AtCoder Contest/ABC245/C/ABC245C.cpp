#include<bits/stdc++.h>
using namespace std;
const int N = 2000010;
int n, k;
int a[N], b[N], f[N][2];
signed main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++)cin >> a[i];
	for(int i = 1; i <= n; i++)cin >> b[i];
	f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i][0] |= ((abs(a[i] - a[i - 1]) <= k && f[i - 1][0]) || (abs(a[i] - b[i - 1]) <= k && f[i - 1][1]));
		f[i][1] |= ((abs(b[i] - a[i - 1]) <= k && f[i - 1][0]) || (abs(b[i] - b[i - 1]) <= k && f[i - 1][1]));
	}
	if(f[n][0] | f[n][1])puts("Yes");
	else puts("No");
	return 0;
}
