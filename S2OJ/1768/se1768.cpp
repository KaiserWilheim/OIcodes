#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
int w[5];
bool chq(int a, int b, int c, int d)
{
	if(c < 0 || d < 0)return false;
	if(w[1] > a + b / 2 + c / 2 + d / 4)return false;
	if(w[2] > b + a / 2 + d / 2 + c / 4)return false;
	if(w[3] > c + a / 2 + d / 2 + b / 4)return false;
	if(w[4] > d + b / 2 + c / 2 + a / 4)return false;
	return true;
}
int main()
{
	for(int i = 1; i <= 4; i++)
		scanf("%d", &w[i]);
	int ans = 1e9;
	for(int a = 0; a <= w[1]; a++)
	{
		for(int b = 0; b <= w[2]; b++)
		{
			int tmpc = w[3] - a / 2 - b / 4,
				tmpd = w[4] - a / 4 - b / 2;
			int cd = (tmpc + tmpd) / 3;
			int c2 = tmpc - cd,
				d2 = tmpd - cd;
			int c, d;
			if(c2 + d2 - cd == 2)
			{
				c = c2 * 2 - 1;
				d = d2 * 2 - 1;
				if(c < 0)c = 0, d = tmpd;
				else if(d < 0)d = 0, c = tmpc;
				if(chq(a, b, c, d))
					ans = min(ans, a + b + c + d);
			}
			else if(c2 + d2 - cd == 1)
			{
				c = c2 * 2 - 1;
				d = d2 * 2;
				if(c < 0)c = 0, d = tmpd;
				else if(d < 0)d = 0, c = tmpc;
				if(chq(a, b, c, d))
					ans = min(ans, a + b + c + d);
				c = c2 * 2;
				d = d2 * 2 - 1;
				if(c < 0)c = 0, d = tmpd;
				else if(d < 0)d = 0, c = tmpc;
				if(chq(a, b, c, d))
					ans = min(ans, a + b + c + d);
			}
			else
			{
				c = c2 * 2;
				d = d2 * 2;
				if(c < 0)c = 0, d = tmpd;
				else if(d < 0)d = 0, c = tmpc;
				if(chq(a, b, c, d))
					ans = min(ans, a + b + c + d);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}