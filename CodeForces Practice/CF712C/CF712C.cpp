#include<bits/stdc++.h>
using namespace std;
int a[3];
int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	a[0] = a[1] = a[2] = y;
	int tot = 0;
	while((a[0] < x) || (a[1] < x) || (a[2] < x))
	{
		tot++;
		sort(a, a + 3);
		a[0] = a[1] + a[2] - 1;
	}
	printf("%d\n", tot);
	return 0;
}
