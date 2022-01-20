#include<bits/stdc++.h>
using namespace std;
const int N = 205;
int n, m;
int a[N];
int f[N][N];
inline void update(int k)
{
	for(int i = 0; i < n; i++)for(int j = 0; j < n; j++)if(f[i][j] > f[i][k] + f[j][k])f[i][j] = f[j][i] = f[i][k] + f[j][k];
	return;
}
int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)scanf("%d", a + i);
	memset(f, 0x3f, sizeof(f));
	for(int i = 0; i < n; i++)f[i][i] = 0;
	int s1, s2, s3;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &s1, &s2, &s3);
		f[s1][s2] = f[s2][s1] = s3;
	}
	int q;
	cin >> q;
	int now = 0;
	for(int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &s1, &s2, &s3);
		while(a[now] <= s3 && now < n)
		{
			update(now);
			now++;
		}
		if(a[s1] > s3 || a[s2] > s3)cout << -1 << endl;
		else
		{
			if(f[s1][s2] == 1e9)cout << -1 << endl;
			else cout << f[s1][s2] << endl;
		}
	}
	return 0;
}
