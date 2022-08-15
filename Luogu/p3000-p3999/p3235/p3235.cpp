#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = 100010;
int T, F, n;
int a[N];
int sg[M], vis[M];
int main()
{
	scanf("%d%d", &T, &F);
	for(int i = F; i <= 100000; i++)
	{
		int r;
		for(int j = 2; j <= i; j = r + 1)
		{
			int tmp = i / j;
			r = i / (i / j);
			int flag = ((j == r) ? 1 : 2);
			int num = 0;
			while(num < flag)
			{
				num++;
				int res = 0;
				if((i % j) & 1)res ^= sg[tmp + 1];
				if((j - i % j) & 1)res ^= sg[tmp];
				j++;
				vis[res] = i;
			}
		}
		for(int j = 0;; j++)
		{
			if(vis[j] != i)
			{
				sg[i] = j;
				break;
			}
		}
	}
	while(T--)
	{
		scanf("%d", &n);
		int res = 0;
		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			res ^= sg[a[i]];
		}
		if(res)printf("1 ");
		else printf("0 ");
	}
	return 0;
}
