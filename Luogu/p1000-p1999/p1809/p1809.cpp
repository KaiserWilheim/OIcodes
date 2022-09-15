#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
ll ans;
int a[N];
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + 1 + n);
	while(n > 3)
	{
		ans += min(a[1] * 2 + a[n] + a[n - 1], a[1] + a[2] * 2 + a[n]);
		n -= 2;
	}
	if(n == 1)ans += a[1];
	else if(n == 2)ans += a[2];
	else if(n == 3)ans += a[1] + a[2] + a[3];
	cout << ans << endl;
	return 0;
}