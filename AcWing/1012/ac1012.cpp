#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010;
int n;
struct Node
{
	int x, y;
	bool operator < (const Node &a)const
	{
		return x < a.x;
	}
}a[N];
int f[N];
int main()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		f[i] = 1;
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + 1 + n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
			if(a[i].y > a[j].y)
				f[i] = max(f[i], f[j] + 1);
		maxn = max(maxn, f[i]);
	}
	printf("%d\n", maxn);
	return 0;
}
