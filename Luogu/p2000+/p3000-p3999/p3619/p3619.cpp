#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
struct task
{
	int t, b;
}f[N], g[N];
bool cmp1(task &x, task &y)
{
	return x.t < y.t;
}
bool cmp2(task &x, task &y)
{
	return x.t + x.b > y.t + y.b;
}
int main()
{
	int z, n, k;
	scanf("%d", &z);
	while(z--)
	{
		int d = 0, e = 0;
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if(b <= 0)
			{
				f[++d] = { a,b };
			}
			else
			{
				g[++e] = { a,b };
			}
		}
		if(d!=0)sort(f + 1, f + d + 1, cmp2);
		if(e!=0)sort(g + 1, g + e + 1, cmp1);
		bool flag = false;
		for(int i = 1; i <= e; i++)
		{
			if(k > g[i].t)
			{
				k += g[i].b;
			}
			else
			{
				puts("-1s");
				flag = true;
				break;
			}
		}
		for(int i = 1; i <= d; i++)
		{
			if(k > f[i].t)
			{
				k += f[i].b;
			}
			else
			{
				puts("-1s");
				flag = true;
				break;
			}
			if(k <= 0)
			{
				puts("-1s");
				flag = true;
				break;
			}
		}
		if(flag)continue;
		puts("+1s");
	}
	return 0;
}
