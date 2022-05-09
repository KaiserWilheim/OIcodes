#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a, b, x, y;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if(!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll z = x;
	x = y, y = z - y * (a / b);
	return d;
}

int main()
{
	cin >> a >> b;
	exgcd(a, b, x, y);
	cout << (x % b + b) % b << endl;
	return 0;
}