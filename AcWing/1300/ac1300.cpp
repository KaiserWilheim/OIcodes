#include<bits/stdc++.h>
using namespace std;
int p, e, i, d, t;
int main()
{
	while(cin >> p >> e >> i >> d, ~p && ~e && ~i && ~d)
	{
		int l = 21252;
		int ans = (5544 * p + 14421 * e + 1288 * i - d + l) % l;
		cout << "Case " << ++t << ": the next triple peak occurs in " << (ans ? ans : l) << " days.\n";
	}
	return 0;
}
