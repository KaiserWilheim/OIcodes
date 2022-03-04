#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010;
int a[N], d1[N], d2[N], n;
bool read(int &x)
{
	char c = getchar();
	if(c == EOF)return false;
	while(c > '9' || c < '0')c = getchar();
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return true;
}
int main()
{
	while(read(a[++n]));
	n--;
	int ans = 1, idx = 1;
	d1[1] = d2[1] = a[1];
	for(int i = 2; i <= n; i++)
	{
		if(d1[ans] >= a[i])
		{
			d1[++ans] = a[i];
		}
		else
		{
			*upper_bound(d1 + 1, d1 + 1 + ans, a[i], greater<int>()) = a[i];
		}
		if(d2[idx] < a[i])
		{
			d2[++idx] = a[i];
		}
		else
		{
			*lower_bound(d2 + 1, d2 + 1 + idx, a[i]) = a[i];
		}
	}
	printf("%d\n%d\n", ans, idx);
	return 0;
}
