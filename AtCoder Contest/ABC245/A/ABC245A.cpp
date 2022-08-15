#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	b += a * 60, d += c * 60;
	if(d < b)puts("Aoki");
	else puts("Takahashi");
	return 0;
}
