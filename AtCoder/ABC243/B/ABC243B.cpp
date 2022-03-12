#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], b[N];
int main()
{
	int n;
	scanf("%d", &n);
	multiset<int>q;
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		q.insert(b[i]);
		if(a[i] == b[i])cnt++;
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		res += q.count(a[i]);
	}
	printf("%d\n%d\n", cnt, res - cnt);
	return 0;
}
