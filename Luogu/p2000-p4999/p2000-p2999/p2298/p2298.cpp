#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
char reich[N][N];
bool vis[N][N];
int n, m;
int stx, sty;
struct sudatusu
{
	int x, y, step;
};
queue<sudatusu>q;
bool chq(int x, int y)
{
	if(x < 0)return false;
	if(x >= n)return false;
	if(y < 0)return false;
	if(y >= m)return false;
	if(vis[x][y])return false;
	if(reich[x][y] == '#')return false;
	return true;
}
void bfs(int x, int y, int now)
{
	if(reich[x][y] == 'd')
	{
		cout << now << endl;
		exit(0);
		return;
	}
	if(chq(x + 1, y))
	{
		sudatusu p = { x + 1, y, now + 1 };
		q.push(p);
		vis[x + 1][y] = true;
	}
	if(chq(x, y + 1))
	{
		sudatusu p = { x, y + 1, now + 1 };
		q.push(p);
		vis[x][y + 1] = true;
	}
	if(chq(x - 1, y))
	{
		sudatusu p = { x - 1, y, now + 1 };
		q.push(p);
		vis[x - 1][y] = true;
	}
	if(chq(x, y - 1))
	{
		sudatusu p = { x, y - 1, now + 1 };
		q.push(p);
		vis[x][y - 1] = true;
	}
	if(q.empty())return;
	vis[x][y] = true;
	sudatusu p = q.front();
	q.pop();
	bfs(p.x, p.y, p.step);
	return;

}
int main()
{
	scanf("%d%d", &n, &m);
	bool flag = false;
	for(int i = 0; i < n; i++)
	{
		scanf("%s", reich[i]);
		if(!flag)
		{
			for(int j = 0; j < m; j++)
			{
				if(reich[i][j] == 'm')
				{
					stx = i, sty = j;
					flag = true;
					break;
				}
			}
		}

	}
	bfs(stx, sty, 0);
	cout << "No Way!" << endl;
	return 0;
}
