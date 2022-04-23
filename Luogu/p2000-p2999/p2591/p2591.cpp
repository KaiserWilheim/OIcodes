#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long n, k;
	cin >> n >> k;
	long long ans = (n == 1) ? 1 : ((k <= (n >> 1 | 1)) ? k : (n - k + 1)) << 1;
	cout << ans << endl;
	return 0;
}
