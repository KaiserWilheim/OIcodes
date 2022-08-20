#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
struct Raindrop
{
	int x, y;
	bool operator < (const Raindrop &a)const
	{
		return x < a.x;
	}
}a[N];
int t[N], b[N];
int h1, t1, h2, t2;
int main()
{
	int d;
	scanf("%d%d", &n, &d);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + 1 + n);

	int ans = 1e9;
	h1 = h2 = 1;
	for(int l = 1, r = 0; l <= n; l++)
	{
		while(h1 <= t1 && t[h1] < l)h1++;
		while(h2 <= t2 && b[h2] < l)h2++;
		while(a[t[h1]].y - a[b[h2]].y < d && r < n)
		{
			r++;
			while(h1 <= t1 && a[t[t1]].y < a[r].y)t1--;
			t[++t1] = r;
			while(h2 <= t2 && a[b[t2]].y > a[r].y)t2--;
			b[++t2] = r;
		}
		if(a[t[h1]].y - a[b[h2]].y >= d)
			ans = min(ans, a[r].x - a[l].x);
	}
	if(ans >= 1e9)ans = -1;
	printf("%d\n", ans);
	return 0;
}