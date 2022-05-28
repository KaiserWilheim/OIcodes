#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int m, n;
	int x1, y1, x2, y2;
	bool flag = true;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		char s[110];
		scanf("%s", &s);
		for(int j = 0; j < m; j++)
		{
			if(s[j] == 'o')
			{
				if(flag)x1 = i, y1 = j, flag = false;
				else x2 = i, y2 = j;
			}
		}
	}
	printf("%d\n", (abs(x1 - x2) + abs(y1 - y2)));
	return 0;
}
