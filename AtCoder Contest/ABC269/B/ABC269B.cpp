#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int main()
{
	int a = 10, b = 0, c = 10, d = 0;
	for(int i = 1; i <= 10; i++)
	{
		string s;
		cin >> s;
		if(s != "..........")
		{
			a = min(a, i);
			b = max(b, i);
			for(int j = 1; j <= 10; j++)
			{
				if(s[j - 1] == '#')
				{
					c = min(c, j);
					d = max(d, j);
				}
			}
		}
	}
	printf("%d %d\n%d %d\n", a, b, c, d);
	return 0;
}