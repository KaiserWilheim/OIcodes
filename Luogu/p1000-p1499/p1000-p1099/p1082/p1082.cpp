#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll x, y;
void exgcd(ll a, ll b)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b);
	ll z = x;
	x = y;
	y = z - a / b * y;
	return;
}
int main()
{
	ll a, b;
	cin >> a >> b;
	exgcd(a, b);
	x = (x % b + b) % b;
	cout << x << endl;
	return 0;
}
