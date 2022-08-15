#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);
		if(n <= 5)puts("-1");
		else
		{
			if(n & 1)printf("3 %d\n", n - 3);
			else printf("2 %d\n", n - 2);
		}
	}
	return 0;
}
