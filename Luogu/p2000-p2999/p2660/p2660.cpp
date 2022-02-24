#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long x, y;
	long long ans = 0;
	cin >> x >> y;
	while(x*y!=0)
	{
		if(x < y)swap(x, y);
		ans += (x / y) * 4 * y;
		x = x % y;
	}
	cout << ans << endl;
	return 0;
}
