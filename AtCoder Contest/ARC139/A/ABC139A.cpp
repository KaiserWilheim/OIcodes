#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int a[N];
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)cin >> a[i];
	ll now = 1ll << a[1];
	for(int i = 2; i <= n; i++)
	{
		ll base = 1ll << a[i];
		ll temp = now / base;
		temp++;
		if(temp % 2 == 0 && temp != 1)temp++;
		now = base * temp;
	}
	cout << now << endl;
	return 0;
}
