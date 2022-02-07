#include<bits/stdc++.h>
using namespace std;
vector<int>matrix[100010];
int main()
{
	int h, w;
	cin >> h >> w;
	for(int i = 1; i <= h; i++)
	{
		for(int j = 1; j <= w; j++)
		{
			int x;
			scanf("%d", &x);
			matrix[i].push_back(x);
		}
	}
	for(int i = 1; i <= w; i++)
	{
		for(int j = 1; j <= h; j++)
		{
			printf("%d ", matrix[j][i - 1]);
		}
		putchar('\n');
	}
	return 0;
}
