#include<bits/stdc++.h>
using namespace std;
int n, k;
long long ans;
void dfs(int res, int now, int pre)
{
	if(now == 2)
	{
		ans += (res / 2) - max(pre, 1) + 1;
		return;
	}
	for(int i = max(pre, 1); i <= (res / now); i++)
	{
		dfs(res - i, now - 1, i);
	}
	return;
}
int main()
{
	cin >> n >> k;
	dfs(n, k, -1);
	cout << ans << endl;
	return 0;
}
