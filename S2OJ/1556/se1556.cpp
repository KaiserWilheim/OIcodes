#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
void solve()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if(a == 1 && d == 1)
	{
		if(c == 0)
		{
			cout << 1 << endl;
			cout << "A " << b << endl;
		}
		else
		{
			cout << 3 << endl;
			cout << "B 1" << endl;
			cout << "A " << -c << endl;
			cout << "B 3" << endl;
		}
	}
	else if(a == -1 && d == -1)
	{
		if(c == 0)
		{
			cout << 2 << endl;
			cout << "A " << -b << endl;
			cout << "B 2" << endl;
		}
		else
		{
			cout << 3 << endl;
			cout << "B 1" << endl;
			cout << "A " << c << endl;
			cout << "B 1" << endl;
		}
	}
	else if(b == 1 && c == -1)
	{
		if(a == 0)
		{
			cout << 2 << endl;
			cout << "B 1" << endl;
			cout << "A " << -d << endl;
		}
		else
		{
			cout << 2 << endl;
			cout << "A " << -a << endl;
			cout << "B 1" << endl;
		}
	}
	else if(b == -1 && c == 1)
	{
		if(a == 0)
		{
			cout << 3 << endl;
			cout << "B 1" << endl;
			cout << "A " << d << endl;
			cout << "B 2" << endl;
		}
		else
		{
			cout << 2 << endl;
			cout << "A " << a << endl;
			cout << "B 3" << endl;
		}
	}
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}