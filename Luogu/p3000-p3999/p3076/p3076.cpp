#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int st[N], ed[N];
ll ans = 0;
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> st[i] >> ed[i];
		ans += abs(ed[i] - st[i]);
	}
	st[++n] = m, ed[n] = 0;
	sort(st + 1, st + 1 + n);
	sort(ed + 1, ed + 1 + n);
	for(int i = 1; i <= n; i++)
		ans += abs(ed[i] - st[i]);
	cout << ans << endl;
	return 0;
}