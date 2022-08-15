#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, ans = 1e18;
int calc(int a, int b)
{
	return a * a * a + a * a * b + a * b * b + b * b * b;
}
signed main()
{
	cin >> n;
	for(int a = 0; a <= 1000000; a++)
	{
		int l = -1, r = 1000001;
		while(l < r - 1)
		{
			int mid = (l + r) >> 1;
			if(calc(a, mid) >= n)r = mid; 
			else l = mid;
		}
		ans = min(ans, calc(a, r));
	}
	cout << ans << "\n";
	return 0; 
}
