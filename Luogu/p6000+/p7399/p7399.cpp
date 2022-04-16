#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int h[N];
int tt = 0;
int main()
{
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		while(tt && h[tt] > x)tt--;
		if(tt && h[tt] == x)continue;
		if(x)
		{
			ans++;
			h[++tt] = x;
		}
	}
	cout << ans << endl;
	return 0;
}
