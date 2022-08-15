#include<bits/stdc++.h>
using namespace std;
int main()
{
	int v, a, b, c;
	scanf("%d%d%d%d", &v, &a, &b, &c);
	v %= (a + b + c);
	v -= a;
	if(v < 0)
	{
		puts("F");
		return 0;
	}
	v -= b;
	if(v < 0)
	{
		puts("M");
		return 0;
	}
	v -= c;
	if(v < 0)
	{
		puts("T");
		return 0;
	}
	return 0;
}
