#include<bits/stdc++.h>
using namespace std;
int h[10010];
int main()
{
	int lf, tp, rt;
	while(scanf("%d%d%d", &lf, &tp, &rt) == 3)
	{
		for(int i = lf; i < rt; i++)
		{
			h[i] = max(h[i], tp);
		}
	}
	for(int i = 1; i <= 10010; i++)
	{
		if(h[i] != h[i - 1])
		{
			cout << i << " " << h[i] << " ";
		}
	}
	return 0;
}
