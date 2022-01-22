#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int d = 19260817;
inline int read()
{
	int res = 0, ch = getchar();
	while(!isdigit(ch) and ch != EOF)
		ch = getchar();
	while(isdigit(ch))
	{
		res = (res << 3) + (res << 1) + (ch - '0');
		res %= d;
		ch = getchar();
	}
	return res;
}
int x, y;
void exgcd(int a, int b)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b);
	int z = x;
	x = y;
	y = z - a / b * y;
	return;
}
int main()
{
	int a=read(), b=read();
	if(b == 0)
	{
		puts("Angry!");
		return 0;
	}
	exgcd(b, d);
	x = (x % d + d) % d;
	printf("%lld\n", a * ( ll )(x) % d);
	return 0;
}
