#include<bits/stdc++.h>
using namespace std;
int num[100010];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i < 4 * n; i++)
	{
		int x;
		scanf("%d", &x);
		num[x]++;
	}
	for(int i = 1; i<= n; i++)
	{
		if(num[i] == 3)
		{
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}
