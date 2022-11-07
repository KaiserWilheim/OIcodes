#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
int n;
int a[N], b[N];
bool chq(int x)
{
	int les = 0, gre = 0;
	if(a[x] == 1 || a[x] == n)return false;
	for(int i = 1; i <= n; i++)
	{
		if(i == x)continue;
		if(a[i] > a[x])
		{
			gre++;
			b[i] = 1;
		}
		else
		{
			les++;
			b[i] = 0;
		}
	}
	int sum = 0, c = 0, del;
	if(les < gre)c = 1;
	del = abs(les - gre);
	for(int i = 1; i < x; i++)
	{
		if(b[i] == c)sum++;
		else sum = max(sum - 1, 0);
		if(sum == 3)
			sum = 1, del -= 2;
	}
	sum = 0;
	for(int i = x + 1; i <= n; i++)
	{
		if(b[i] == c)sum++;
		else sum = max(sum - 1, 0);
		if(sum == 3)
			sum = 1, del -= 2;
	}
	return del <= 0;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++)
		{
			if(chq(i))putchar('1');
			else putchar('0');
		}
		putchar('\n');
	}
	return 0;
}
