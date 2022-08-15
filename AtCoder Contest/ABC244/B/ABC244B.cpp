#include <bits/stdc++.h>
using namespace std;
string s;
int xx[5] = { 1,0,-1,0 };
int yy[5] = { 0,-1,0,1 };
int main()
{
	int n;
	cin >> n >> s;
	int x = 0, y = 0, pos = 0;
	for(int i = 1; i <= n; i++)
	{
		if(s[i-1] == 'R')
		{
			pos = (pos + 1) % 4;
		}
		else
		{
			x += xx[pos];
			y += yy[pos];
		}
	}
	printf("%d %d\n", x, y);
	return 0;
}
