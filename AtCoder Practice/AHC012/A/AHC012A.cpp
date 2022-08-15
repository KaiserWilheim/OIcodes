#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20010;
int sum1[N], sum2[N];
int a[12];
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	printf("%d\n", k - (k % 2));
	for (int i = 1; i <= 10; i++)scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x += 10000, y += 10000;
		sum1[x]++, sum2[y]++;
	}
	for (int i = 2; i <= 20000; i++)
		sum1[i] += sum1[i - 1], sum2[i] += sum2[i - 1];
	int prev = 0, now = 1;
	int pre = 0;
	for (int i = 1; i <= 20000; i++)
	{
		if (sum1[i] - prev >= now * a[now])
		{
			printf("%d %d %d %d\n", i - 10000, 1, i - 10000, -1);
			prev = sum1[i];
			pre = i;
			now++;
		}
		if (now == 10)break;
	}
	k -= 9;
	int per = n / k - 1;
	pre = 0;
	for (int i = 1; i <= 20000; i++)
	{
		if (sum2[i] - sum2[pre] >= per)
		{
			printf("%d %d %d %d\n", 1, i - 10000, -1, i - 10000);
			k--;
			pre = i;
			if (k < 1)break;
		}
	}
	return 0;
}
//score:69910307 
