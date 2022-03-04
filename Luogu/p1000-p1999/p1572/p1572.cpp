#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int gcd(int x, int y)
{
	if(y == 0)return x;
	else return gcd(y, x % y);
}
signed main()
{
	cin >> s;
	if(isdigit(s[0]))s = '+' + s;
	int i = 0;
	int a = 0, b = 1;
	while(i != s.length())
	{
		int c = 0, d = 0;
		bool flag = (s[i++] == '+') ? true : false;
		while(isdigit(s[i]))c = c * 10 + s[i++] - '0';
		i++;
		while(isdigit(s[i]))d = d * 10 + s[i++] - '0';
		a = a * d + (flag ? 1 : -1) * b * c;
		b = b * d;
		int g = gcd(a, b);
		a /= g;
		b /= g;
	}
	int g = gcd(a, b);
	a /= g;
	b /= g;
	if(b < 0)
	{
		a = -a;
		b = -b;
	}
	if(b == 1)printf("%lld\n", a);
	else printf("%lld/%lld\n", a, b);
	return 0;
}

