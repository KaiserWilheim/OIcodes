#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
int a[N], ind[N];
priority_queue<int, vector<int>, greater<int>>q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		scanf("%d", &a[i]);
		ind[a[i]]++;
	}
	printf("%d\n", a[1]);
	for(int i = 1; i <= n; i++)
		if(!ind[i])q.push(i);
	for(int i = n - 1; i >= 1; i--)
	{
		int u = q.top();
		q.pop();
		printf("%d %d\n", a[i], u);
		ind[a[i]]--;
		if(!ind[a[i]])q.push(a[i]);
	}
	return 0;
}