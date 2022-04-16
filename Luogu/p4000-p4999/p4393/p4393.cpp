#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
ll a[N];
ll ans;
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> a[i];
	for(int i = 2; i <= n; i++)
		ans += max(a[i], a[i - 1]);
	cout << ans << endl;
	return 0;
}
