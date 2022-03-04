#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int reich[N][N];
int dis[N];
bool vis[N];
int n;
int prim()
{
	int res = 0;
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	for(int i = 1; i <= n; i++)
	{
		int t = -1;
		for(int j = 1; j <= n; j++)
		{
			if((!vis[j]) && ((t == -1) || (dis[t] > dis[j])))t = j;
		}
		res += dis[t];
		vis[t] = true;
		for(int j = 1; j <= n; j++)dis[j] = min(dis[j], reich[t][j]);
	}
	return res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)scanf("%d", &reich[i][j]);
	}
	cout << prim() << endl;
	return 0;
}
