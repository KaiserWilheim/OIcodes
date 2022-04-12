#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	double a, b, c;
	cin >> a >> b;
	c = sqrt(a * a + b * b);
	cout << a / c << " " << b / c << endl;
	return 0;
}
