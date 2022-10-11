#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
const int N = 5010, M = 10010;
int n, m;
char s[N][N];
int ans[M];
pair<int, int>q[M];
int tt;
int minn[M];
int last[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= m; i++)
	{
		tt = 1;
		minn[1] = 0x3f3f3f3f;
		q[1] = mp(i, 0);
		for(int j = 1; j <= n; j++)
		{
			if(s[j][i] == '#')last[j] = i;
			while(tt && q[tt].first <= last[j])tt--;
			q[++tt] = mp(last[j], j);
			if(tt == 1)minn[tt] = 0x3f3f3f3f;
			else minn[tt] = min(minn[tt - 1], q[tt].first + q[tt - 1].second);
			if(s[j][i] == '.')ans[i + j - minn[tt]]++;
		}
	}
	for(int i = 1; i <= n + m; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}