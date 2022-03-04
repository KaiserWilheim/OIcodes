#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
bool reich[N][N], vis[N][N];
int n;
int stx, sty, edx, edy;
struct sudatusu
{
	int x, y, step;
};
queue<sudatusu>q;
bool chq(int x, int y)
{
	if(x <= 0)return false;
	if(x > n)return false;
	if(y <= 0)return false;
	if(y > n)return false;
	if(vis[x][y])return false;
	if(reich[x][y])return false;
	return true;
}
void bfs(int x, int y, int now)
{
	if((x == edx) && (y == edy))
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
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		for(int j = 1; j <= n; j++)
		{
			reich[i][j] = s[j - 1] - '0';
		}
	}
	scanf("%d%d%d%d", &stx, &sty, &edx, &edy);
	bfs(stx, sty, 0);
	return 0;
}
