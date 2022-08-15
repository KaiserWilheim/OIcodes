#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
	int n, minn = 0x3f3f3f3f;
	scanf("%d", &n);
	int cnt = 0;
	for(int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		if(x < minn)minn = x, cnt = 1;
		else if(x == minn)cnt++;
	}
	if(cnt <= n / 2)puts("Alice");
	else puts("Bob");
	return 0;
}
