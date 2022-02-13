#include <bits/stdc++.h>
using namespace std;
const int N = 10000010;
int num[N], ans[N];
int main()
{
	int n;
	cin >> n;
	for(int i = 2; i < n; i += 2)
	{
		for(int j = 1; j * (i + 1) <= n; j++)
		{
			if(((j * i) ^ (j * (i + 1))) == j)num[j * (i + 1)]++;
		}
	}
	for(int i = 2; i <= n; i++)ans[i] = ans[i - 1] + num[i];
	printf("%d\n",ans[n]);
	return 0;
}
