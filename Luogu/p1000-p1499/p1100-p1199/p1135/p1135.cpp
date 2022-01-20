#include<bits/stdc++.h>
using namespace std;
int n, a, b;
int k[210];
bool vis[210];
queue< pair<int, int> >q;
void search(int p, int now)
{
	if(p == b)
	{
		cout << now << endl;
		exit(0);
		return;
	}
	if(k[p] == 0)return;
	vis[p] = true;
	if((p - k[p] > 0) && (!vis[p - k[p]]))q.push(make_pair(p - k[p], now + 1));
	if((p + k[p] <= n) && (!vis[p + k[p]]))q.push(make_pair(p + k[p], now + 1));
	if(q.empty())return;
	int x = (q.front()).first, y = (q.front()).second;
	q.pop();
	search(x, y);
	return;
}
int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 1; i <= n; i++)scanf("%d", &k[i]);
	search(a, 0);
	cout << -1 << endl;
	return 0;
}
