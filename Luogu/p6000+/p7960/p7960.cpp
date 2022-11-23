#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000100;
bool valid(int x)
{
	while(x)
	{
		if(x % 10 == 7)return false;
		x /= 10;
	}
	return true;
}
int n, k;
bool vis[N];
int ne[N];
void init()
{
	int pre = 1;
	for(int i = 2; i <= 1e7 + 10; i++)
	{
		if(vis[i])continue;
		if(valid(i))
		{
			ne[pre] = i;
			pre = i;
		}
		else
		{
			for(int j = 1; j * i <= 1e7 + 10; j++)
				vis[i * j] = true;
		}
	}
}
int main()
{
	init();
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		if(vis[n])puts("-1");
		else printf("%d\n", ne[n]);
	}
	return 0;
}
