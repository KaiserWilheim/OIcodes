#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
int n, m;
int a;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i=1;i<=2;i++)
	{
		for(int j = 1; j <= 2; j++)
		{
			scanf("%d", &a);
			if(i == n && j == m)printf("%d\n", a);
		}
	}
	return 0;
}
