#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
double n;
double f[N], g[N];
int main()
{
	cin >> n;
	for(int i = n - 1; i >= 0; i--)
	{
		f[i] = f[i + 1] + (n / (n - i));
		g[i] = f[i] * (1.0 * i / (n - i)) + f[i + 1] + g[i + 1] + (n / (n - i));
	}
	printf("%.2lf\n", g[0]);
	return 0;
}