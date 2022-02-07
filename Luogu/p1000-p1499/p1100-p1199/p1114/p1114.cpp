#include <bits/stdc++.h>
using namespace std;
int l[200010], r[200010], sum1, sum0, ans, n;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x; cin >> x;
		sum1 += (x == 1), sum0 += (x == 0);
		int t = sum0 - sum1 + n;
		if(!l[t] && t != n) l[t] = i;
		else r[t] = i;
	}
	for(int i = 0; i <= 2 * n; i++) ans = max(ans, r[i] - l[i]);
	cout << ans << endl;
	return 0;
}
