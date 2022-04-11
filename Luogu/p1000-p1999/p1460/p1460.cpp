#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int N = 110;
int v, g, minn = INF, len;
int vet[N], food[N][N], save[N], ans[N];
bool vis[N];
bool chq(int len)
{
	int cow[N];
	memset(cow, 0, sizeof(cow));
	for(int i = 1; i <= len; i++)
	{
		for(int l = 1; l <= v; l++)
			cow[l] += food[save[i]][l];
	}
	for(int i = 1; i <= v; i++)
	{
		if(cow[i] < vet[i])
			return false;
	}
	return true;
}
void dfs()
{
	if(len > g || len > minn)
		return;
	if(chq(len) == true)
	{
		if(minn > len)
		{
			minn = len;
			for(int i = 1; i <= minn; i++)
				ans[i] = save[i];
		}
		return;
	}
	int st = save[len];
	for(int i = st; i <= g; i++)
	{
		if(vis[i] == false)
		{
			vis[i] = true;
			len++;
			save[len] = i;
			dfs();
			vis[i] = false;
			save[len] = 0;
			len--;
		}
	}
}
int main()
{
	scanf("%d", &v);
	for(int i = 1; i <= v; i++)
		scanf("%d", &vet[i]);
	scanf("%d", &g);
	for(int i = 1; i <= g; i++)
		for(int l = 1; l <= v; l++)
			scanf("%d", &food[i][l]);
	dfs();
	printf("%d ", minn);
	for(int i = 1; i <= minn; i++)
		printf("%d ", ans[i]);
	return 0;
}
