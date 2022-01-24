#include<bits/stdc++.h>
using namespace std;
char reich[510][510];
bool vis[510][510];
int h, w;
bool chq(int x, int y)
{
	if(x < 0)return false;
	if(x >= h)return false;
	if(y < 0)return false;
	if(y >= w)return false;
	if(reich[x][y] == '#')return false;
	if(vis[x][y])return false;
	return true;
}
void dfs(int x, int y)
{
	if(reich[x][y] == 'g')
	{
		puts("Yes");
		exit(0);
		return;
	}
	vis[x][y] = true;
	if(chq(x + 1, y))dfs(x + 1, y);
	if(chq(x, y + 1))dfs(x, y + 1);
	if(chq(x - 1, y))dfs(x - 1, y);
	if(chq(x, y - 1))dfs(x, y - 1);
	return;
}
int main()
{
	scanf("%d%d", &h, &w);
	int stx = -1, sty = -1;
	for(int i = 0; i < h; i++)
	{
		scanf("%s", &reich[i]);
		if(stx == -1 && sty == -1)
		{
			for(int j = 0; j < w; j++)
			{
				if(reich[i][j] == 's')
				{
					stx = i; sty = j;
					break;
				}
			}
		}
	}
	dfs(stx, sty);
	puts("No");
	return 0;
}
