#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
int n;
int a[N], b[N];
int maxn[N];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> a[i];
	for(int i = 1; i <= n; i++)cin >> b[i];
	for(int i = n; i > 1; i--)maxn[i] = max(maxn[i + 1], b[i]);
	int res = 0;
	for(int i = 1; i < n; i++)res = max(res, maxn[i + 1] - a[i]);
	cout << res << endl;
	return 0;
}