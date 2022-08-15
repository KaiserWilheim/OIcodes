#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a;
	cin >> a;
	a += (1ll << 31);
	if((a < 0) || (a >= (1ll << 32)))puts("No");
	else puts("Yes");
	return 0;
}
