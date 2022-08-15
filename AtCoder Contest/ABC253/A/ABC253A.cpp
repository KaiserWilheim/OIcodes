#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if(a <= b && b <= c)puts("Yes");
	else if(a >= b && b >= c)puts("Yes");
	else puts("No");
	return 0;
}
